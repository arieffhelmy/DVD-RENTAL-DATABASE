#include "Header.hpp"


void displayCustomerData() {
    vector<Customer> customers;

    Customer customer;

    string header;

    ifstream input("customers.csv");

    if (!input.is_open()) {
        cout << "Cannot open the file." << '\n';
        return;
    }


    // Skip the header row (if present)
    getline(input, header);

    // Read customer data from the file
    while (getline(input, header)) {
        stringstream ss(header);

        getline(ss, customer.name, ',');
        getline(ss, customer.phone, ',');
        getline(ss, customer.email, ',');
        getline(ss, customer.customerID, ',');

        customers.push_back(customer);
    }

    input.close();

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

    Customer customer;
    Rental rental;
    DVD dvd;

    string header;

    ifstream input("RentHistory.csv");

    if (!input.is_open()) {
        cout << "Cannot open the file." << '\n';
        return;
    }

    
    // Skip the header row (if present)
    getline(input, header);

    // Read customer data from the file
    while (getline(input, header)) {
        stringstream ss(header);

        getline(ss, customer.customerID, ','); // Date field
        getline(ss, customer.name, ','); // Customer name
        getline(ss, dvd.title, ','); // Customer ID
        getline(ss, rental.Rentdate, ','); // Movie title
        getline(ss, rental.Returndate, ','); // Movie title

        // Add to respective vectors
        rentalHistory.push_back(rental);
        customers.push_back(customer);
        dvdCollection.push_back(dvd);
    }

    input.close();

    // Display all customer data
    cout << "\nRental history:\n";
    for (size_t i = 0; i < customers.size(); ++i) {
        cout << "\nName: " << customers[i].name << '\n';
        cout << "Customer ID: " << customers[i].customerID << '\n';
        cout << "Movie Title: " << dvdCollection[i].title << '\n';
        cout << "Rent Date: " << rentalHistory[i].Rentdate << '\n';
        cout << "Return Date: " << rentalHistory[i].Returndate << '\n';
        cout << "-------------------" << '\n';
    }
}
