import os
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Define the schema for the portfolio table
db.execute(
    """
    CREATE TABLE IF NOT EXISTS portfolio (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER NOT NULL,
        symbol TEXT NOT NULL,
        shares INTEGER NOT NULL,
        price NUMERIC NOT NULL,
        FOREIGN KEY(user_id) REFERENCES users(id)
    )
"""
)


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portfolio = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
        user_id=session["user_id"],
    )

    cash = db.execute(
        "select cash FROM users WHERE id = :user_id", user_id=session["user_id"]
    )[0]["cash"]

    total_value = cash
    grand_total = cash

    for stock in portfolio:
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        stock["value"] = stock["price"] * stock["total_shares"]
        total_value += stock["value"]
        grand_total += stock["value"]

    # Render the portfolio HTML template and pass the data
    return render_template(
        "index.html",
        portfolio=portfolio,
        cash=cash,
        total_value=total_value,
        grand_total=grand_total,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # Check if symbol and shares are provided
        if not symbol:
            return apology("Symbol is required")

        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology(
                "Shares is required and must be provide a positive integer number of shares"
            )

        quote = lookup(symbol)
        if quote is None:
            return apology("Symbol not found")

        price = quote["price"]
        total_cost = int(shares) * price
        user_cash = db.execute(
            "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
        )[0]["cash"]

        if user_cash < total_cost:
            return apology("Not enough cash")

        # Update user's cash
        db.execute(
            "UPDATE users SET cash = cash - :total_cost WHERE id = :user_id",
            total_cost=total_cost,
            user_id=session["user_id"],
        )

        # Insert a transaction record
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
            user_id=session["user_id"],
            symbol=symbol,
            shares=shares,
            price=price,
        )

        flash(f"Bought {shares} shares of {symbol} for {usd(total_cost)}!")

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = ? ORDER BY timestamp DESC", user_id
    )
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    session.clear()
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("Must provide username", 403)
        elif not request.form.get("password"):
            return apology("Must provide password", 403)

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("Invalid username and/or password", 403)

        session["user_id"] = rows[0]["id"]
        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    session.clear()
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        if not quote:
            return apology("Invalid symbol", 400)
        return render_template("quote.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # Get user input from the form
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check if any of the fields are empty
        if not username or not password or not confirmation:
            return apology("All fields must be filled", 400)

        # Check if the passwords match
        if password != confirmation:
            return apology("Passwords do not match. Please try again.", 400)

        # Check if the username already exists in the database
        existing_user = db.execute("SELECT id FROM users WHERE username = ?", username)

        if existing_user:
            return apology(
                "Username already exists. Please choose a different one.", 400
            )

        # Hash the password
        hashed_password = generate_password_hash(password)

        # Insert the user into the "users" table in the database
        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            hashed_password,
        )

        flash("Registration successful! You can now log in.", "success")
        return redirect(url_for("login"))

    # If it's a GET request, just render the registration form
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
        user_id=session["user_id"],
    )

    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # Check if symbol and shares are provided
        if not symbol:
            return apology("Symbol is required")
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology(
                "Shares is required and must provide a positive integer number of shares"
            )
        else:
            shares = int(shares)

        for stock in stocks:
            if stock["symbol"] == symbol:
                if stock["total_shares"] < shares:
                    return apology("not enough shares")
                else:
                    quote = lookup(symbol)
                    if quote is None:
                        return apology("Symbol not found")
                    price = quote["price"]
                    total_sale = shares * price

                    db.execute(
                        "UPDATE users SET cash = cash + :total_sale WHERE id = :user_id",
                        total_sale=total_sale,
                        user_id=session["user_id"],
                    )

                    db.execute(
                        "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (:user_id, :symbol, :shares, :price)",
                        user_id=session["user_id"],
                        symbol=symbol,
                        shares=-shares,
                        price=price,
                    )

                    flash(f"Sold {shares} shares of {symbol} for {usd(total_sale)}!")
                    return redirect("/")

        return apology("symbol not found")
    else:
        return render_template("sell.html", stocks=stocks)
