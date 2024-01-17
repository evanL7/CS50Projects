from cs50 import get_float


def main():
    while True:  # Get user input
        change_owed = get_float("Change owed: ")
        if change_owed >= 0:
            break

    quarters = int(change_owed / 0.25)
    change_owed -= quarters * 0.25

    change_owed = round(change_owed, 2)  # Prevent any imprecision in rounding

    dimes = int(change_owed / 0.1)
    change_owed -= dimes * 0.1

    change_owed = round(change_owed, 2)

    nickels = int(change_owed / 0.05)
    change_owed -= nickels * 0.05

    change_owed = round(change_owed, 2)

    pennies = int(change_owed / 0.01)

    num_coins = quarters + dimes + nickels + pennies  # Records the sum of coins
    print(num_coins)


if __name__ == "__main__":
    main()
