# Same as mario less but draw another pyramid next to the first
# Print mario pyramids
from cs50 import get_int
# Ask height of pyromid
while True:
    height = get_int("Height: ")
    if 0 < height < 9:
        break
# draw Pyromid
for i in range(height):
    spaces = height - 1
    while spaces > i:
        print(" ", end="")
        spaces -= 1
    for j in range(i + 1):
        print("#", end="")
    print("  ", end="")
    # draw second half of pyromid
    for k in range(i + 1):
        print("#", end="")
    print()
