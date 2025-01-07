#include <iostream>

#include "Header.hpp"

int main() {
    int choice;

    do {
        displayMenu(choice);

        switch (choice) {
        case 1:
            //Check Availability DVD();
            break;
        case 2:
            //Add DVD();
            break;
        case 3:
            //register New Customer();
            break;
        case 4:
            //Search Customer ID();
            break;
        case 5:
            //rent DVD();
            break;
        case 6:
            //return DVD();
            break;
        case 7:
            //importCustomersFromCSV();
            break;
        case 8:
            //importRentalsFromCSV();
            break;
        case 9:
            //cout << "Exiting. Thank you for using our system.\n";
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n";

        }
    } while (choice != 9);

    return 0;
}