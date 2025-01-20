#include "Header.hpp"


int main() {
    int choice;

    do {
        displayMenu();
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();
        
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid! Please enter number only.\n";
        }
        else {
        switch (choice) {
        case 1:
            CheckAvailability();
            break;
        case 2:
            AddDVDandStock();
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
            displayCustomerData();
            break;
        case 8:
            displayRentalHistory(); 
            break;
        case 9:
            //cout << "Exiting. Thank you for using our system.\n";
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n";

        }
        }
    } while (choice != 9);

    return 0;
}