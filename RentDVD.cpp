#include "Header.hpp"

//NAME : LAI YIN YI
//MATRIX NUMBER : 23304223
//FUNCTION : TO RENT DVD AND TO VALIDATE EVERY CUSTOMER ID


//FUNCTION : TO RENT DVD
void rentDVD() {
    string customerID, customerName;
    string findtitle;
    string rent;

    vector<DVD> dvdCollection;
    vector<Customer> customers;
    vector<Rental> rentalHistory;

    DVD dvd;
    Rental rental;


    if (!CustomerID(customerID, customerName)) 
    {
        return;
    }


    fstream file;
    string header; 

    file.open("DATA FILES/DVD_Rental_Database.csv", ios::in);

    if (file.fail()) 
    {
        cout << "ERROR" << '\n';
        return;
    }

    getline(file, header);

    while (getline(file, rent)) 
    {
        stringstream ss(rent);
        getline(ss, dvd.title, ',');
        getline(ss, dvd.genre, ',');
        getline(ss, dvd.year, ',');
        ss >> dvd.nostock;
        dvdCollection.push_back(dvd);
    }
    file.close();

    cout << "What is the name of the movie: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    getline(cin, findtitle);
    findtitle = normalizeString(findtitle);  

    bool foundtitle = false;

    // Find and rent the movie
    for (auto& d : dvdCollection) 
    {
        if (findtitle == normalizeString(d.title)) 
        {
            foundtitle = true;
            if (d.nostock > 0) 
            { 
                d.nostock--;
            } else 
            {
                cout << "Movie '" << findtitle << "' is currently out of stock." << endl;
                return;
            }
            break;
        }
    }

    if (!foundtitle) 
    {
        cout << "\nMovie not found: " << findtitle << '\n';
        return;
    } else 
    {
        cout << "\nThe stock for '" << findtitle << "' has been updated." << '\n';
    }

    cout << "How many days would you like to rent the movie? ";
    cin >> rental.rentalPeriod;

    file.open("DATA FILES/DVD_Rental_Database.csv", ios::out | ios::trunc);

    if (file.fail()) 
    {
        cout << "ERROR" << '\n';
        return;
    }

    file << header << '\n';

    for (const auto& d : dvdCollection) 
    {
        file << d.title << ',' << d.genre << ',' << d.year << ',' << d.nostock << '\n';
    }
    file.close();

    // Record rental in RentHistory.csv (including rental period and rental date)
    ofstream output;

    output.open("DATA FILES/RentHistory.csv", ios::app);

    cout << "\n\nCustomerID: " << customerID << '\n'
         << "CustomerName: " << customerName << '\n'
         << "Title: " << findtitle << '\n'
         << "Rental Date: " << rental.rentdate << '\n'
         << "Rental Period: " << rental.rentalPeriod << " days" << endl;

    if (output.is_open()) 
    {
        output << customerID << "," << customerName << "," << findtitle << "," << rental.rentdate << "," << "," << rental.rentalPeriod << endl;  // Leave return date empty for now

        cout << "\nData written to RentHistory.csv successfully." << endl;
    } else 
    {
        cout << "\nError opening RentHistory.csv." << endl;
    }

    output.close();
}


//FUNCTION : TO VALIDATE EVERY CUSTOMER ID
bool CustomerID(string& customerID, string& customerName) 
{

    Customer customer;
    string findcustomerID, Return;

    fstream file("DATA FILES/customers.csv", ios::in | ios::out);

    if (file.fail()) 
    {
        cout << "ERROR" << '\n';
        return false;
    }

    bool foundcustomerID = false;

    cout << "Enter customer ID: ";
    cin >> findcustomerID;

    while (getline(file, Return)) 
    {
        stringstream ss(Return); 
        

        getline(ss, customer.name, ',');
        getline(ss, customer.phone, ',');
        getline(ss, customer.email, ',');
        getline(ss, customer.customerID, ',');

        // Check if the customerID matches
        if (normalizeString(findcustomerID) == customer.customerID) 
        {
            foundcustomerID = true;
            customerID = findcustomerID; 
            customerName = customer.name; 
            break;
        }
    }

    if (!foundcustomerID) 
    {
        cout << "Invalid customer ID" << endl;
    }
    file.close();

    return foundcustomerID;
}
