#include "Header.hpp"

unordered_map<string, Customer> loadCustomerData(const string& filePath) {
    ifstream file(filePath);
    unordered_map<string, Customer> customerDatabase;

    if (!file.is_open()) {
        cout << "Error: Could not open file " << filePath << endl;
        return customerDatabase;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, customerID, phone, email;

        // Read customer data from the line
        getline(ss, name, ',');
        getline(ss, customerID, ',');
        getline(ss, phone, ',');
        getline(ss, email);

        Customer customer(name, customerID, phone, email);
        customerDatabase[customerID] = customer;
    }

    file.close();
    return customerDatabase;
}

void displayCustomerData(const unordered_map<string, Customer>& customerDatabase) {
    cout << "\nCustomer Data Imported:" << endl;
    for (const auto& customerPair : customerDatabase) {
        const Customer& customer = customerPair.second;
        cout << "Name: " << customer.getName()
             << ", CustomerID: " << customer.getID()
             << ", Phone: " << customer.phone
             << ", Email: " << customer.email << endl;
    }
}

vector<Rental> loadRentalHistory(const string& filePath) {
    ifstream file(filePath);
    vector<Rental> rentalHistory;

    if (!file.is_open()) {
        cout << "Error: Could not open file " << filePath << endl;
        return rentalHistory;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string customerID, movieTitle;

        getline(ss, customerID, ',');
        getline(ss, movieTitle);

        Rental rental(stoi(customerID), movieTitle);
        rentalHistory.push_back(rental);
    }

    file.close();
    return rentalHistory;
}

void displayRentalHistory(const vector<Rental>& rentalHistory) {
    cout << "\nRental History Imported:" << endl;
    for (const Rental& rental : rentalHistory) {
        cout << "CustomerID: " << rental.customerID
             << ", Movie Title: " << rental.DVDTitle << endl;
    }
}
