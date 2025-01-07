#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

// DVD Class
class DVD {
public:
    string title;
    string genre;
    int year;
    bool isAvailable;

    // Constructor
    DVD(string t, string g, int y) : title(t), genre(g), year(y), isAvailable(true) {}
};

// Customer Class
class Customer {
public:
    string name;
    int customerID;

    // Constructor
    Customer(string n, int id) : name(n), customerID(id) {}

    // Member functions
    string getName() const {
        return name;
    }

    int getID() const {
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


#endif