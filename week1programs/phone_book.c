#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Name: ");
    int age = get_int("Age: ");
    string phone_number = get_string("Phone number: ");

    printf("%s, %i years old and phone number %s\n", name, age, phone_number);
}