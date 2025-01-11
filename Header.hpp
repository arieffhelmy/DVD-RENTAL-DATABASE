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

// Customer Class
class Customer {
public:
    string name;
    string customerID;
    string phone;
    string email;


    // Constructor
    Customer(string n,  string customerID, string phone, string email);
    Customer() : name(""), phone(""), email(""), customerID("") {}
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

int displayMenu(int);
void CheckAvailability();
void AddDVD();
void returnDVD();  


#endif