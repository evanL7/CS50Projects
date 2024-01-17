#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: "); // Sets size of array
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i); // Stores amount of hours into array
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A'); // Ensures correct output

    printf("%.1f hours\n", calc_hours(hours, weeks, output)); // Rounds to one decimal place
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    float sum = 0;
    for (int i = 0; i < weeks; i++) // This loop gets the sum of hours
    {
        sum += hours[i];
    }

    if (output == 'T')
    {
        return sum; // Returns the total amount of hours
    }
    else
    {
        return sum / weeks; // Returns the average amount of hours
    }
}