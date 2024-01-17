from cs50 import get_int


def main():
    height = get_height()
    for i in range(1, height + 1):  # Prints out the text to console
        print(" " * (height - i) + "#" * i)


def get_height():
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:  # Exits only when condition is met
            return height


if __name__ == "__main__":
    main()
