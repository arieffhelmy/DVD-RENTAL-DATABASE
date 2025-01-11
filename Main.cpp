#include <iostream>

#include "Header.hpp"


int main() {
    int choice;

    do {
        void displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
        case 1:
            CheckAvailability();
            break;
        case 2:
            AddDVD();
            break;
        case 3:
            registerCustomer();
            break;
        case 4:
            searchCustomer();
            break;
        case 5:
            rentDVD();
            break;
        case 6:
            returnDVD();
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