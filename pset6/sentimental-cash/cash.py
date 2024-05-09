# CS50 cash python program
from cs50 import get_float

# Ask for change
change = get_float("Change: \n")


def main():
    while True:
        if change > 0:
            break


cents = change * 100
total = int(change * 100)
coins = 0

# Calculate the change
for i in range(total):
    if cents - 25 >= 0:
        cents = cents - 25
        coins += 1
    elif cents - 10 >= 0:
        cents = cents - 10
        coins += 1
    elif cents - 5 >= 0:
        cents = cents - 5
        coins += 1
    elif cents - 1 >= 0:
        cents = cents - 1
        coins += 1
# Print the change
print(coins)
main()