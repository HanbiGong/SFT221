/* -----------------------------------------------------------
Name : Hanbi Gong            
Seneca email : hgong12@myseneca.ca         
Seneca Student ID : 111932224
Date : Jan 24th, 2024

***********************************************************************/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "customer.h"

bool isValidPostalCode(const char postalCode[])
{
    int i = 0;
    char formattedPostalCode[MAX_LENGTH];

    for (int j = 0; postalCode[j] != '\0'; j++)
    {
        if (!isspace(postalCode[j]))
        {
            formattedPostalCode[i] = toupper(postalCode[j]);
            i++;
        }
    }
    formattedPostalCode[i] = '\0';

    // Check if the postal code has the correct format
    if (strlen(formattedPostalCode) != 6)
    {
        return false;
    }

    for (int j = 0; j < 6; j++)
    {
        if ((j % 2 == 0 && !isalpha(formattedPostalCode[j])) || (j % 2 == 1 && !isdigit(formatted_Postal_Code[j])))
        {
            return false;
        }
    }

    return true;
}


Customer CustomerInformation()
{
    Customer customer;

    // Prompt the user to enter the customer information
    printf("Enter your first name: ");
    while (fgets(customer.firstName, MAX_LENGTH, stdin))
    {
        if (customer.firstName[0] != '\n') 
        {
            customer.firstName[strlen(customer.firstName) - 1] = '\0';
            break;
        }
        printf("Invalid Entry: Enter your first name: ");
    }

    printf("Enter your last name: ");
    while (fgets(customer.lastName, MAX_LENGTH, stdin)) 
    {
        if (customer.lastName[0] != '\n')
        {
            customer.lastName[strlen(customer.lastName) - 1] = '\0';
            break;
        }
        printf("Invalid Entry: Enter your last name: ");
    }

    printf("Enter your street address: ");
    while (fgets(customer.streetAddress, MAX_LENGTH, stdin)) 
    {
        if (customer.streetAddress[0] != '\n')
        {
            customer.streetAddress[strlen(customer.streetAddress) - 1] = '\0';
            break;
        }
        printf("Invalid Entry: Enter your street address: ");
    }

    printf("Enter your city: ");
    while (fgets(customer.city, MAX_LENGTH, stdin)) 
    {
        if (customer.city[0] != '\n')
        {
            customer.city[strlen(customer.city) - 1] = '\0';
            break;
        }
        printf("Invalid Entry: Enter your city: ");
    }

    printf("Enter your province: ");
    while (fgets(customer.province, MAX_LENGTH, stdin)) 
    {
        if (customer.province[0] != '\n')
        {
            customer.province[strlen(customer.province) - 1] = '\0';
            break;
        }
        printf("Invalid Entry: Enter your province: ");
    }

    printf("Enter your postal code: ");
    while (fgets(customer.postalCode, MAX_LENGTH, stdin))
    {
        if (isValidPostalCode(customer.postalCode))
        {
            for (int i = 0; customer.postalCode[i] != '\0'; i++)
            {
                customer.postalCode[i] = toupper(customer.postalCode[i]);
            }
                break;
        }
        printf("Invalid Entry: Enter your postal code: ");
    }

    return customer;
}

int main()
{
    Customer customer = CustomerInformation();
    printf("\nYou entered:\n");
    printf("%s %s\n", customer.firstName, customer.lastName);
    printf("%s,\n", customer.streetAddress);
    printf("%s, %s,\n", customer.city, customer.province);
    printf("%s", customer.postalCode);

    return 0;
}

