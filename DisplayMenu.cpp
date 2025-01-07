#include "Header.hpp"

int displayMenu(int Choice) 
{
    cout << "\n--- DVD Rental System ---\n";
    cout << "1. Check Availability DVD\n";
    cout << "2. Add DVDs\n";
    cout << "3. Register New Customer\n";
    cout << "4. Search Customer ID\n";
    cout << "5. Rent DVD\n";
    cout << "6. Return DVD\n";
    cout << "7. Customer Data\n";
    cout << "8. Rental History\n";
    cout << "9. Exit\n";

    cout << "Enter your choice: ";
    cin >> Choice;

    return Choice;
}
