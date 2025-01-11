#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <ctime>

using namespace std;

// DVD Class
class DVD {
public:
    string title;
    string genre;
    string year;
    int nostock;

    // Constructor
    //DVD(string t, string g, int y) : title(t), genre(g), year(y), isAvailable(true) {}
};

class Customer {
public:
    string name;
    string customerID;
    string phone;
    string email;

    // Constructor with correct initialization order
    Customer(string n, string id, string ph, string em)
        : name(n), customerID(id), phone(ph), email(em) {}

    // Default Constructor
    Customer() : name(""), customerID(""), phone(""), email("") {}

    // Member functions
    string getName() const {
        return name;
    }

    string getID() const {
        return customerID;
    }
};


// Rental Class
class Rental {
public:
    int customerID;
    string DVDTitle;

    // Constructor
    Rental(int id, string title) : customerID(id), DVDTitle(title) {}
};

extern vector<DVD> dvdCollection;
extern vector<Customer> customers;

void displayMenu();
void CheckAvailability();
void AddDVD();
void registerCustomer();
void searchCustomer();
void rentDVD();
void returnDVD();
bool CustomerID(string);
//void displayCustomerData();
//void displayRentalHistory();




#endif