# This program is gonna ask user for name and greeting him
from cs50 import get_string

# Prompt for input
# name = input("What is your name?\n")
name = get_string("What is your name?\n")

# print name
print("Hello, " + name)