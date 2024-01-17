import string
from cs50 import get_string


def main():
    user_input = get_string("Text: ")

    letters = count_letters(user_input)
    words = count_words(user_input)
    sentences = count_sentences(user_input)

    L = (letters / words) * 100
    S = (sentences / words) * 100

    index = 0.0588 * L - 0.296 * S - 15.8
    index = round(index)  # Rounds index to nearest integer

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_letters(text):
    text = text.split()  # Splits text into a list
    count = 0

    for i in text:  # Iterates through the list
        for character in i:  # Iterates through each character
            if character in string.ascii_letters:
                count += 1

    return count


def count_words(text):
    text = text.split()
    return len(text)


def count_sentences(text):
    text = text.split()
    count = 0

    for i in text:
        if (
            i[-1] == "." or i[-1] == "!" or i[-1] == "?"
        ):  # Checks the last character for punctuation
            count += 1

    return count


if __name__ == "__main__":
    main()
