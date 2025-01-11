#include "Header.hpp"


void displayCustomerData() {
    vector<Customer> customers;

    ifstream ip("customers.csv");

    if (!ip.is_open()) {
        cout << "ERROR: Unable to open the file." << '\n';
        return;
    }

    string line;
    // Skip the header row (if present)
    getline(ip, line);

    // Read customer data from the file
    while (getline(ip, line)) {
        stringstream ss(line);
        Customer customer;

        getline(ss, customer.name, ',');
        getline(ss, customer.phone, ',');
        getline(ss, customer.email, ',');
        getline(ss, customer.customerID, ',');

        customers.push_back(customer);
    }

    ip.close();

    // Display all customer data
    cout << "Customer Data:\n";
    for (const auto& customer : customers) {
        cout << "\nName: " << customer.name << '\n';
        cout << "Phone: " << customer.phone << '\n';
        cout << "Email: " << customer.email << '\n';
        cout << "Customer ID: " << customer.customerID << '\n';
        cout << "-------------------" << '\n';
    }
}



void displayRentalHistory() {
    vector<Rental> rentalHistory;
    vector<DVD> dvdCollection;
    vector<Customer> customers;

    ifstream ip("RentHistory.csv");

    if (!ip.is_open()) {
        cout << "ERROR: Unable to open the file." << '\n';
        return;
    }

    string line;
    // Skip the header row (if present)
    getline(ip, line);

    // Read customer data from the file
    while (getline(ip, line)) {
        stringstream ss(line);
        Customer customer;
        Rental rental;
        DVD dvd;

        getline(ss, rental.dates, ','); // Date field
        getline(ss, customer.name, ','); // Customer name
        getline(ss, customer.customerID, ','); // Customer ID
        getline(ss, dvd.title, ','); // Movie title

        // Add to respective vectors
        rentalHistory.push_back(rental);
        customers.push_back(customer);
        dvdCollection.push_back(dvd);
    }

    ip.close();

    // Display all customer data
    cout << "Rental history:\n";
    for (size_t i = 0; i < customers.size(); ++i) {
        cout << "\nDate: " << rentalHistory[i].dates << '\n';
        cout << "Name: " << customers[i].name << '\n';
        cout << "Customer ID: " << customers[i].customerID << '\n';
        cout << "Movie Title: " << dvdCollection[i].title << '\n';
        cout << "-------------------" << '\n';
    }
}
