#include "Header.hpp"

//NAME
//MATRIX NUMBER
//FUNCTION

void rentDVD() 
{
    // Ask for the customer ID first, only proceed if valid
    if (!CustomerID()) 
    {
        cout << "Cannot proceed with DVD return due to invalid customer ID." << endl;
        return;
    }

    DVD dvd;
    Customer customer;
    string findtitle;
    string line;
    stringstream updatedContent;

    // Open the file for reading and writing (in text mode)
    fstream file("DVD_Rental_Database.csv", ios::in | ios::out);

    if (!file.is_open()) 
    {
        cout << "ERROR: Unable to open the file." << '\n';
        return; 
    }

    bool foundtitle = false;

    // Prompt user to enter the movie title
    cout << "What is the name of the movie: ";
    getline(cin, findtitle);  // Read movie title from the user

    // Read the entire file content and process it line by line
    while (getline(file, line)) 
    {
        stringstream ss(line);  // Using stringstream to process each line

        // Read the title, genre, year, and stock from the line
        getline(ss, dvd.title, ',');
        getline(ss, dvd.genre, ',');
        getline(ss, dvd.year, ',');
        ss >> dvd.nostock;

        // Update stock if the title matches
        if (findtitle == dvd.title) 
        {
            foundtitle = true;
            dvd.nostock--;  // Increment the stock for the movie
        }

        // Write the modified line to the new content
        updatedContent << dvd.title << ',' << dvd.genre << ',' << dvd.year << ',' << dvd.nostock << '\n';
    }

    file.close(); // Close the file after reading

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

    file << updatedContent.str();
    file.close();

    if (foundtitle) 
    {
        ofstream op("RentHistory.csv", ios::app);  // Open in append mode to add new records

        if (!op.is_open()) 
        {
            cout << "ERROR: Unable to open RentHistory.csv." << '\n';
            return;
        }
    
        time_t now = time(0);
        tm *ltm = localtime(&now);

        // Write only the updated movie to the RentHistory file
        op << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year <<','
           << customer.name << ","
           << customer.customerID << ","
           << dvd.title << ","
           << "Rent" << endl;

        cout << "DVD added to RentHistory successfully!" << '\n';

        op.close();
    }
    return;
}



//NAME: 
//MATRIX NUMBER: 
//FUNCTION: 

void returnDVD() 
{
    // Ask for the customer ID first, only proceed if valid
    if (!CustomerID()) 
    {
        cout << "Cannot proceed with DVD return due to invalid customer ID." << endl;
        return;
    }

    DVD dvd;
    Customer customer;
    string findtitle;
    string line;
    stringstream updatedContent;

    // Open the file for reading and writing (in text mode)
    fstream file("DVD_Rental_Database.csv", ios::in | ios::out);

    if (!file.is_open()) 
    {
        cout << "ERROR: Unable to open the file." << '\n';
        return; 
    }

    bool foundtitle = false;

    // Prompt user to enter the movie title
    cout << "What is the name of the movie: ";
    getline(cin, findtitle);  // Read movie title from the user

    // Read the entire file content and process it line by line
    while (getline(file, line)) 
    {
        stringstream ss(line);  // Using stringstream to process each line

        // Read the title, genre, year, and stock from the line
        getline(ss, dvd.title, ',');
        getline(ss, dvd.genre, ',');
        getline(ss, dvd.year, ',');
        ss >> dvd.nostock;

        // Update stock if the title matches
        if (findtitle == dvd.title) 
        {
            foundtitle = true;
            dvd.nostock++;  // Increment the stock for the movie
        }

        // Write the modified line to the new content
        updatedContent << dvd.title << ',' << dvd.genre << ',' << dvd.year << ',' << dvd.nostock << '\n';
    }

    file.close(); // Close the file after reading

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

    file << updatedContent.str();
    file.close();

    if (foundtitle) 
    {
        ofstream op("RentHistory.csv", ios::app);  // Open in append mode to add new records

        if (!op.is_open()) 
        {
            cout << "ERROR: Unable to open RentHistory.csv." << '\n';
            return;
        }
    
        time_t now = time(0);
        tm *ltm = localtime(&now);

        // Write only the updated movie to the RentHistory file
        op << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year <<','
           << customer.name << ","
           << customer.customerID << ","
           << dvd.title << ","
           << "Return" << endl;
           

        cout << "DVD added to RentHistory successfully!" << '\n';

        op.close();
    }
    return;
}




// CustomerID function to verify customer
bool CustomerID()
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

