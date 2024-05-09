from cs50 import get_string
import re

# Ask number for Credit Card
while True:
    number = get_string("Number: ")
    lenght = len(number)

    if lenght > 0:
        break

# check valid nomber with Luhn’s Algorithm
integer = int(number)

take_digit = 0
digit_position = 1
product2 = 0
summ = 0
sum_odd_even = 0
sum_prod_even = 0

while integer > 0:
    take_digit = integer % 10

    # if position is even
    if digit_position % 2 == 0:
        product2 = take_digit * 2
        # we need to add up each digit. If more than 9 then add tens and numbers separately
        sum_prod_even += int(product2 / 10) + (product2 % 10)

    # if position is odd
    else:
        summ = summ + take_digit
    integer /= 10
    integer = int(integer)
    digit_position += 1

# add the sums of odd digits and multiplied by 2 even ones
sum_odd_even = summ + sum_prod_even

check = sum_odd_even % 10

# find kind of card by the first numbers
if re.fullmatch('5[1 - 5]\d{14}', number) and not (check):
    print("MASTERCARD")
elif (re.fullmatch('3[47]\d{13}', number)) and not (check):
    print("AMEX")
elif not (check) and (re.fullmatch('4\d{12}', number) or re.fullmatch('4\d{15}', number)):
    print("VISA")
else:
    print("INVALID")