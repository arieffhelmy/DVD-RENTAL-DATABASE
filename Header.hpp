#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cctype>

using namespace std;

// DVD Class
class DVD 
{
public:
    string title;
    string genre;
    string year;
    int nostock;

    // Constructor
    DVD() = default;
};

class Customer 
{
public:
    string name;
    string customerID;
    string phone;
    string email;

    // Constructor
    Customer() = default;
};


// Rental Class
class Rental 
{
public:
    string DVDTitle;
    string returnStatus, Rentdate, Returndate;
    int rentalPeriod;
    
    time_t now = std::time(0);              
    tm *ltm = std::localtime(&now);         
    
    string rentdate= to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" +to_string(1900 + ltm->tm_year);
    string returndate= to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" +to_string(1900 + ltm->tm_year);

    // Constructor
    Rental() = default;
};

extern vector<DVD> dvdCollection;
extern vector<Customer> customers;
extern vector<Rental> rentalHistory;
extern vector<string> rentHistoryReturn;

void displayMenu();
void CheckAvailability();
void AddDVDandStock();
void registerCustomer();
void searchCustomer();
void rentDVD();
void returnDVD();
void displayCustomerData();
void displayRentalHistory();
bool CustomerID(string& customerID, string& customerName);
string normalizeString(const string& input);
string generateCustomerID();

#endif