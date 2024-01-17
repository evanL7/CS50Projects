#include <cs50.h>
#include <stdio.h>

int check_amex(unsigned long long card);
int check_mastercard(unsigned long long card);
int check_visa(unsigned long long card);

int main(void)
{
    unsigned long long card;
    do
    {
        card = get_long("Number: "); // Can't get to work because user input returns negative because of overflow
    }
    while (card < 1);

    int total_eod = 0; // total of every other digit
    for (unsigned long long i = 100; i < 100000000000000000; i *= 100)
    {
        unsigned long long parsed = 2 * ((card % i) / (i / 10));
        // printf("parsed: %llu\n", parsed);

        if (parsed > 9)
        {
            total_eod++; // greatest number in tens digit is one since 9 * 2 = 18
            int ones = parsed % 10;
            total_eod += ones;
        }
        else
        {
            total_eod += parsed;
        }
    }
    //printf("Total_eod: %i\n", total_eod);

    int total_not_multiplied = 0; // total of the numbers that weren't mutiplied
    unsigned long long split_num;
    for (unsigned long long j = 10; j < 100000000000000000; j *= 100)
    {
        if (j == 10)
        {
            split_num = card % j;
        }
        else
        {
            split_num = (card % j) / (j / 10);
        }

        total_not_multiplied += split_num;
    }
    //printf("total_not_multiplied: %i\n", total_not_multiplied);


    int total_checksum = total_eod + total_not_multiplied;

    if ((total_checksum % 10) == 0) // Checks checksum
    {
        if (check_amex(card))
        {
            printf("AMEX\n");
        }
        else if (check_mastercard(card))
        {
            printf("MASTERCARD\n");
        }
        else if (check_visa(card))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}

int check_amex(unsigned long long card) // Checks American Express card type
{
    if (card / 10000000000000 >= 34 && card / 10000000000000 < 35) // Checks if card between 34
    {
        return 1;
    }
    else if (card / 10000000000000 >= 37 && card / 10000000000000 < 38) // Checks if card between 37
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_mastercard(unsigned long long card) // Checks Mastercard type
{
    if (card / 100000000000000 >= 51 && card / 100000000000000 < 56)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int check_visa(unsigned long long card) // Checks Visa card type
{
    if (card / 1000000000000 < 10 && card / 1000000000000 >= 4 && card / 1000000000000 < 5)
    {
        return 1;
    }
    else if (card / 1000000000000000 < 10 && card / 1000000000000000 >= 4 && card / 1000000000000000 < 5)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}