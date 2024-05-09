from cs50 import get_string
import math


def main():

    text_input = get_string("Text: ")
    index_value = get_index(text_input)

    # Conditions to output the reading index
    if index_value < 1:
        print("Before Grade 1")
    elif index_value >= 16:
        print("Grade 16+")
    else:
        print("Grade " + str(index_value))

# Reads text as a parameter and returns the index which determines approximate grade level


def get_index(text):

    # Initializing all the values to zero
    word_count = 0
    sentence_count = 0
    letter_count = 0
    textlength = len(text)

    # Counts the number of letters, words and sentences in the string of text
    for i in range(0, textlength):
        if (text[i].isalpha()):
            letter_count += 1

        if ((i == 0 and text[i] != ' ') or (text[i] == ' ' and text[i + 1] != ' ')):
            word_count += 1

        if (text[i] == '.' or text[i] == '?' or text[i] == '!'):
            sentence_count += 1

    # Calculating L and S values for the formula
    L = (letter_count / word_count) * 100.0
    S = (sentence_count / word_count) * 100.0

    # Calculating grade level using Coleman-Liau index formula
    index = round(0.0588 * L - 0.296 * S - 15.8)
    return index


main()