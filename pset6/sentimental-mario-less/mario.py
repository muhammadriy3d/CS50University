# Print mario pyramids
from cs50 import get_int

while True:
    # Prompt for height
    height = get_int('Height: ')
    if height <= 0 or height == 9:
        continue
    else:
        # Draw a pyramid using user height
        # For each raw
        for i in range(height):
            # Draw a space to flip the pyramid from left to right
            print("", end=" " * (height - i - 1))
            # For each column
            for j in range(i + 1):
                # Draw a hash blocks with a formila x - 1
                print("#", end="" * (i - 1))
            # New line
            print()
        break