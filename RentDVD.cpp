#include "Header.hpp"

//NAME : LAI YIN YI
//MATRIX NUMBER : 23304223
//FUNCTION : TO RENT DVD

void rentDVD() {
    string customerID, customerName;
    string findtitle;
    string Return;

    vector<DVD> dvdCollection;
    vector<Customer> customers;
    vector<Rental> rentalHistory;

    DVD dvd;
    Rental rental;

    // Get customer ID and validate it
    if (!CustomerID(customerID, customerName)) {
        cout << "Cannot proceed with DVD rental due to invalid customer ID." << endl;
        return;
    }

    // Read DVD data from file
    fstream file;

    file.open("DVD_Rental_Database.csv", ios::in);

    if (file.fail()) {
        cout << "ERROR: Unable to open DVD_Rental_Database.csv." << '\n';
        return;
    }

    while (getline(file, Return)) {
        stringstream ss(Return);
        getline(ss, dvd.title, ',');
        getline(ss, dvd.genre, ',');
        getline(ss, dvd.year, ',');
        ss >> dvd.nostock;
        dvdCollection.push_back(dvd);
    }
    file.close();

    // Get movie title from user
    cout << "What is the name of the movie: ";
    cin.ignore(); // Ignore newline character
    getline(cin, findtitle);

    bool foundtitle = false;

    // Find and rent the movie
    for (auto& d : dvdCollection) {
        if (findtitle == d.title) {
            foundtitle = true;
            if (d.nostock > 0) { // Check if stock is available
                d.nostock--;
            } else {
                cout << "Movie '" << findtitle << "' is currently out of stock." << endl;
                return;
            }
            break;
        }
    }

    if (!foundtitle) {
        cout << "Movie not found: " << findtitle << '\n';
        return;
    } else {
        cout << "The stock for '" << findtitle << "' has been updated." << '\n';
    }

    // Get rental period (number of days to rent the movie)
    cout << "How many days would you like to rent the movie? ";
    cin >> rental.rentalPeriod;

    // Update DVD_Rental_Database.csv
    file.open("DVD_Rental_Database.csv", ios::out | ios::trunc);

    if (file.fail()) {
        cout << "ERROR: Unable to open DVD_Rental_Database.csv for writing." << '\n';
        return;
    }

    for (const auto& d : dvdCollection) {
        file << d.title << ',' << d.genre << ',' << d.year << ',' << d.nostock << '\n';
    }
    file.close();

    // Record rental in RentHistory.csv (including rental period and rental date)
    ofstream output;
    
    output.open("RentHistory.csv", ios::app);

    // Debugging: Print details before writing
    cout << "\n\nCustomerID: " << customerID << '\n'
         << "CustomerName: " << customerName << '\n'
         << "Title: " << findtitle << '\n'
         << "Rental Date: " << rental.rentdate << '\n'
         << "Rental Period: " << rental.rentalPeriod << " days" << endl;

    if (output.is_open()) {
        output << customerID << "," << customerName << "," << findtitle << "," << rental.rentdate << "," << "," << rental.rentalPeriod << endl;  // Leave return date empty for now

        cout << "Data written to RentHistory.csv successfully." << endl;
    } else {
        cout << "Error opening RentHistory.csv." << endl;
    }

    output.close();
}

// CustomerID function to verify customer
bool CustomerID(string& customerID, string& customerName) {
    vector<Customer> customers;
    Customer customer;
    string findcustomerID, Return;

    // Open the file for both reading and writing
    fstream file("customers.csv", ios::in | ios::out);

    if (file.fail()) {
        cout << "ERROR: Unable to open the file." << '\n';
        return false;
    }

    bool foundcustomerID = false;

    cout << "Enter customer ID: ";
    cin >> findcustomerID;

    // Read each Return from the file
    while (getline(file, Return)) {
        stringstream ss(Return); // Use stringstream to split the Return by commas
        
        // Parse the fields using getline with the delimiter ','
        getline(ss, customer.name, ',');
        getline(ss, customer.phone, ',');
        getline(ss, customer.email, ',');
        getline(ss, customer.customerID, ',');

        // Check if the customerID matches
        if (findcustomerID == customer.customerID) {
            foundcustomerID = true;
            customerID = findcustomerID; // Update customerID
            customerName = customer.name; // Update customerName
            break;
        }
    }

    // If the customer was not found
    if (!foundcustomerID) {
        cout << "Invalid customer ID" << endl;
    }
    file.close();
    return foundcustomerID;
}
