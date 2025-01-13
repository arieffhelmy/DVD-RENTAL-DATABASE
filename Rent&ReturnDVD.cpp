#include "Header.hpp"

//NAME : LAI YIN YI
//MATRIX NUMBER : 23304223
//FUNCTION : TO RENT DVD

//NAME : NURUL AMIRAH BINTI MOHAMAD YUSOFF
//MATRIX NUMBER : 23301116
//FUNCTION : TO RETURN DVD

// Rent DVD function with vector usage
void rentDVD() 
{
   // Ask for the customer ID first, only proceed if valid
    string customerID;
    if (!CustomerID(customerID)) 
    {
        cout << "Cannot proceed with DVD return due to invalid customer ID." << endl;
        return;
    }

    vector<DVD> dvdCollection;  // Vector to store DVDs
    vector<Customer> customers;  // Vector to store customers
    vector<Rental> rentalHistory;
    DVD dvd;
    Customer customer;
    Rental rental;
    string findtitle;
    string line;

    // Open the file for reading and writing (in text mode)
    fstream file("DVD_Rental_Database.csv", ios::in | ios::out);

    if (!file.is_open()) 
    {
        cout << "ERROR: Unable to open the file." << '\n';
        return; 
    }

    bool foundtitle = false;

    // Read the entire file content and process it line by line
    while (getline(file, line)) 
    {
        stringstream ss(line);  // Using stringstream to process each line

        // Read the title, genre, year, and stock from the line
        getline(ss, dvd.title, ',');
        getline(ss, dvd.genre, ',');
        getline(ss, dvd.year, ',');
        ss >> dvd.nostock;

        // Add the DVD to the vector
        dvdCollection.push_back(dvd);
    }

    // Close the file after reading
    file.close();

    // Read customer information from the "customers.csv" file
    fstream customerFile("customers.csv", ios::in);
    if (!customerFile.is_open()) 
    {
        cout << "ERROR: Unable to open the customers file." << '\n';
        return;
    }

    // Read customer details and populate customerList
    while (getline(customerFile, line)) 
    {
        stringstream ss(line);  // Using stringstream to process each line

        // Parse customer details
        getline(ss, customer.name, ',');
        getline(ss, customer.phone, ',');
        getline(ss, customer.email, ',');
        getline(ss, customer.customerID, ',');

        customers.push_back(customer);
    }

    customerFile.close();

    // Find the customer in the vector by matching customerID
    for (auto& details : customers) 
    {
        if (customerID == details.customerID) 
        {
            customer = details;  // Found the customer, store the details
            break;
        }
    }

    // Prompt user to enter the movie title
    cout << "What is the name of the movie: ";
    cin.ignore();  // To ignore any leftover newline character
    getline(cin, findtitle);  // Read movie title from the user

    // Search for the movie in the vector and update stock if found
    for (auto& d : dvdCollection) 
    {
        if (findtitle == d.title) 
        {
            foundtitle = true;
            d.nostock--;  // Increase the stock for the movie
            break;
        }
    }

    // If the movie was found, inform the user
    if (!foundtitle)
    {
        cout << "Movie not found: " << findtitle << '\n';
    }
    else
    {
        cout << "The stock for '" << findtitle << "' has been updated." << '\n';
    }

    // Now, open the file for writing (to overwrite the old content with the updated one)
    file.open("DVD_Rental_Database.csv", ios::out | ios::trunc);  // Open in write mode and truncate the file

    if (!file.is_open()) 
    {
        cout << "ERROR: Unable to open the file for writing." << '\n';
        return;
    }

    // Write all DVDs back to the file (including updated stock)
    for (const auto& d : dvdCollection)
    {
        file << d.title << ',' << d.genre << ',' << d.year << ',' << d.nostock << '\n';
    }

    file.close();

    // Log the transaction in RentHistory.csv
    if (foundtitle) 
    {
        ofstream op("RentHistory.csv", ios::app);  // Open in append mode to add new records

        if (!op.is_open()) 
        {
            cout << "ERROR: Unable to open RentHistory.csv." << '\n';
            return;
        }

        // Write only the updated movie to the RentHistory file
        op << customer.name << "," << customer.customerID << "," << findtitle << "," << rental.dates << "," << " " << endl;

        cout << "DVD added to RentHistory successfully!" << '\n';

        op.close();
    }
    return;
}

// Return DVD function with vector usage
void returnDVD() 
{
    // Ask for the customer ID first, only proceed if valid
    string customerID;
    if (!CustomerID(customerID)) 
    {
        cout << "Cannot proceed with DVD return due to invalid customer ID." << endl;
        return;
    }

    vector<DVD> dvdCollection;  // Vector to store DVDs
    vector<Customer> customers;  // Vector to store customers
    vector<Rental> rentalHistory;
    DVD dvd;
    Customer customer;
    Rental rental;
    string findtitle;
    string line;

    // Open the file for reading and writing (in text mode)
    fstream file("DVD_Rental_Database.csv", ios::in | ios::out);

    if (!file.is_open()) 
    {
        cout << "ERROR: Unable to open the file." << '\n';
        return; 
    }

    bool foundtitle = false;

    // Read the entire file content and process it line by line
    while (getline(file, line)) 
    {
        stringstream ss(line);  // Using stringstream to process each line

        // Read the title, genre, year, and stock from the line
        getline(ss, dvd.title, ',');
        getline(ss, dvd.genre, ',');
        getline(ss, dvd.year, ',');
        ss >> dvd.nostock;

        // Add the DVD to the vector
        dvdCollection.push_back(dvd);
    }

    // Close the file after reading
    file.close();

    // Read customer information from the "customers.csv" file
    fstream customerFile("customers.csv", ios::in);
    if (!customerFile.is_open()) 
    {
        cout << "ERROR: Unable to open the customers file." << '\n';
        return;
    }

    // Read customer details and populate customerList
    while (getline(customerFile, line)) 
    {
        stringstream ss(line);  // Using stringstream to process each line

        // Parse customer details
        getline(ss, customer.name, ',');
        getline(ss, customer.phone, ',');
        getline(ss, customer.email, ',');
        getline(ss, customer.customerID, ',');

        customers.push_back(customer);
    }

    customerFile.close();

    // Find the customer in the vector by matching customerID
    for (auto& details : customers) 
    {
        if (customerID == details.customerID) 
        {
            customer = details;  // Found the customer, store the details
            break;
        }
    }

    // Prompt user to enter the movie title
    cout << "What is the name of the movie: ";
    cin.ignore();  // To ignore any leftover newline character
    getline(cin, findtitle);  // Read movie title from the user

    // Search for the movie in the vector and update stock if found
    for (auto& d : dvdCollection) 
    {
        if (findtitle == d.title) 
        {
            foundtitle = true;
            d.nostock++;  // Increase the stock for the movie
            break;
        }
    }

    // If the movie was found, inform the user
    if (!foundtitle)
    {
        cout << "Movie not found: " << findtitle << '\n';
    }
    else
    {
        cout << "The stock for '" << findtitle << "' has been updated." << '\n';
    }

    // Now, open the file for writing (to overwrite the old content with the updated one)
    file.open("DVD_Rental_Database.csv", ios::out | ios::trunc);  // Open in write mode and truncate the file

    if (!file.is_open()) 
    {
        cout << "ERROR: Unable to open the file for writing." << '\n';
        return;
    }

    // Write all DVDs back to the file (including updated stock)
    for (const auto& d : dvdCollection)
    {
        file << d.title << ',' << d.genre << ',' << d.year << ',' << d.nostock << '\n';
    }

    file.close();

    // Log the transaction in RentHistory.csv
    if (foundtitle) 
    {
        ofstream op("RentHistory.csv", ios::app);  // Open in append mode to add new records

        if (!op.is_open()) 
        {
            cout << "ERROR: Unable to open RentHistory.csv." << '\n';
            return;
        }

        // Write only the updated movie to the RentHistory file
        op << customer.name << "," << customer.customerID << "," << findtitle << "," << " " << "," << rental.dates << endl;

        cout << "DVD added to RentHistory successfully!" << '\n';

        op.close();
    }
    return;
}



// CustomerID function to verify customer
bool CustomerID(string customerID)
{
    Customer customer;
    string findcustomerID, line;

    // Open the file for both reading and writing
    fstream file("customers.csv", ios::in | ios::out);

    if (!file.is_open()) 
    {
        cout << "ERROR: Unable to open the file." << '\n';
        return false; 
    }

    bool foundcustomerID = false;

    cout << "Enter customer ID: ";
    cin >> findcustomerID;

    // Read each line from the file
    while (getline(file, line)) 
    {
        stringstream ss(line);  // Use stringstream to split the line by commas
        
        // Parse the fields using getline with the delimiter ','
        getline(ss, customer.name, ',');
        getline(ss, customer.phone, ',');
        getline(ss, customer.email, ',');
        getline(ss, customer.customerID, ',');

        // Check if the customerID matches
        if (findcustomerID == customer.customerID) 
        {
            foundcustomerID = true;
            // Display the customer details
            cout << "Name: " << customer.name << '\n';
            cout << "Phone: " << customer.phone << '\n';
            cout << "Email: " << customer.email << '\n';
            break;
        }
    }

    // If the customer was not found
    if (!foundcustomerID) 
    {
        cout << "Invalid customer ID" << endl;
    }

    file.close();
    return foundcustomerID;
}
