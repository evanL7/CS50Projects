#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int amount; // in cents
    do
    {
        amount = get_int("Change owed: ");
    }
    while (amount < 0); // Continues asking user until acceptable input received
    return amount;
}

int calculate_quarters(int cents)
{
    int n = cents / 25; // Floor division of the number of cents
    return n;
}

int calculate_dimes(int cents)
{
    int n = cents / 10; // Floor diviison of the number of cents
    return n;
}

int calculate_nickels(int cents)
{
    int n = cents / 5; // Floor division
    return n;
}

int calculate_pennies(int cents)
{
    int n = cents / 1; // Floor division
    return n;
}
