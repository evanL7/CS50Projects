from cs50 import get_int


def main():
    height = get_height()
    for i in range(1, height + 1):
        print(" " * (height - i) + "#" * i, end="")  # Left side of pyramid
        print("  ", end="")  # Spaces inbetween
        print("#" * i, end="")  # Right side of pyramid
        print()  # Creates new line


def get_height():
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            return height


if __name__ == "__main__":
    main()
