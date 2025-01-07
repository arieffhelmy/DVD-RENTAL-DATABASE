#include <iostream>

#include "Header.hpp"
#include "Register&SearchCustID.cpp"

int main() {
    int choice;

    do {
        int displayMenu(choice);
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
        case 1:
            //Check Availability DVD();
            break;
        case 2:
            //Add DVD();
            break;
        case 3:
            registerCustomer();
            break;
        case 4:
            searchCustomer();
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