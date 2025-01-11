#include "Header.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Customer {
    string name;
    string customerID;
    string phone;
    string email;
};

struct RentalHistory {
    string customerID;
    string movieTitle;
    string rentalDate;
    string returnDate;
};

Customer* loadCustomerData(const string& filePath, int& totalCustomers) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filePath << endl;
        return nullptr;
    }

    string line;
    totalCustomers = 0;

    while (getline(file, line)) {
        totalCustomers++;
    }

    file.clear();
    file.seekg(0, ios::beg);

    Customer* customers = new Customer[totalCustomers];
    int index = 0;

    while (getline(file, line)) {
        size_t start = 0, end = 0;

        end = line.find(',', start);
        customers[index].name = line.substr(start, end - start);

        start = end + 1;
        end = line.find(',', start);
        customers[index].customerID = line.substr(start, end - start);

        start = end + 1;
        end = line.find(',', start);
        customers[index].phone = line.substr(start, end - start);

        start = end + 1;
        customers[index].email = line.substr(start);

        index++;
    }

    file.close();
    return customers;
}

void displayCustomerData(Customer* customers, int totalCustomers) {
    cout << "\nCustomer Data:" << endl;
    for (int i = 0; i < totalCustomers; ++i) {
        cout << "Name: " << customers[i].name
             << ", CustomerID: " << customers[i].customerID
             << ", Phone: " << customers[i].phone
             << ", Email: " << customers[i].email << endl;
    }
}

RentalHistory* loadRentalHistory(const string& filePath, int& totalRentals) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filePath << endl;
        return nullptr;
    }

    string line;
    totalRentals = 0;

    while (getline(file, line)) {
        totalRentals++;
    }

    file.clear();
    file.seekg(0, ios::beg);

    RentalHistory* rentals = new RentalHistory[totalRentals];
    int index = 0;

    while (getline(file, line)) {
        size_t start = 0, end = 0;

        end = line.find(',', start);
        rentals[index].customerID = line.substr(start, end - start);

        start = end + 1;
        end = line.find(',', start);
        rentals[index].movieTitle = line.substr(start, end - start);

        start = end + 1;
        end = line.find(',', start);
        rentals[index].rentalDate = line.substr(start, end - start);

        start = end + 1;
        rentals[index].returnDate = line.substr(start);

        index++;
    }

    file.close();
    return rentals;
}

void displayRentalHistory(RentalHistory* rentals, int totalRentals) {
    cout << "\nRental History Data:" << endl;
    for (int i = 0; i < totalRentals; ++i) {
        cout << "CustomerID: " << rentals[i].customerID
             << ", Movie Title: " << rentals[i].movieTitle
             << ", Rental Date: " << rentals[i].rentalDate
             << ", Return Date: " << rentals[i].returnDate << endl;
    }
}

int main() {

    string customerFilePath = "customer_data.csv";
    string rentalFilePath = "rental_history.csv";

    int totalCustomers = 0;
    Customer* customers = loadCustomerData(customerFilePath, totalCustomers);

    if (customers) {
        displayCustomerData(customers, totalCustomers);
        delete[] customers;
    } else {
        cout << "No customer data loaded." << endl;
    }

    int totalRentals = 0;
    RentalHistory* rentals = loadRentalHistory(rentalFilePath, totalRentals);

    if (rentals) {
        displayRentalHistory(rentals, totalRentals);
        delete[] rentals;
    } else {
        cout << "No rental history data loaded." << endl;
    }

    return 0;
}
