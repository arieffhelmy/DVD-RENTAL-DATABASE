#include "Header.hpp"

struct DVD 
{
    std::string title;
    bool isAvailable;
};

struct Rental 
{
    int customerID;
    std::string dvdTitle;
};

struct Customer 
{
    std::string name;
    int id;
};

std::vector<DVD> dvdCollection;
std::vector<Rental> rentals;
std::vector<Customer> customers;

int main() 
{

    dvdCollection.push_back({"Movie A", false});
    rentals.push_back({101, "Movie A"});

    importCustomersFromCSV();
    importRentalsFromCSV();
    returnDVD();

    return 0;
}

void returnDVD() 
{
    std::string dvdTitle;
    std::cout << "\nEnter DVD title to return : ";
    std::cin.ignore();
    std::getline(std::cin, dvdTitle);

    auto rentalIt = std::find_if(rentals.begin(), rentals.end(), [&](Rental& r) 
    {
        return r.dvdTitle == dvdTitle;
    });

    if (rentalIt == rentals.end()) 
    {
        std::cout << "\nRental record not found! ";
        return;
    }

    auto dvdIt = std::find_if(dvdCollection.begin(), dvdCollection.end(), [&](DVD& d) 
    {
        return d.title == dvdTitle;
    });

    if (dvdIt != dvdCollection.end()) 
    {
        dvdIt->isAvailable = true;
        std::cout << "\nDVD marked as returned and available again! ";
    }

    rentals.erase(rentalIt);
}

void importCustomersFromCSV() 
{
    std::ifstream file("customer_data.csv");
    std::string line;

    if (!file.is_open()) 
    {
        std::cout << "\nError: Unable to open customer data file. ";
        return;
    }

    std::getline(file, line); 
    while (std::getline(file, line)) 
    {
        std::stringstream ss(line);
        std::string idStr, name;

        std::getline(ss, idStr, ',');
        std::getline(ss, name);

        int id = std::stoi(idStr);
        customers.push_back({name, id});
    }

    file.close();
    std::cout << "\nCustomer import finished.";
}

void importRentalsFromCSV() 
{
    std::ifstream inFile("rental_history.csv");
    std::string line;

    if (!inFile.is_open()) 
    {
        std::cout << "\nError: Unable to open rental history file.";
        return;
    }

    std::getline(inFile, line); 
    while (std::getline(inFile, line)) 
    {
        std::stringstream ss(line);
        std::string customerIDStr, dvdTitle;

        std::getline(ss, customerIDStr, ',');
        std::getline(ss, dvdTitle);

        int customerID = std::stoi(customerIDStr);
        rentals.push_back({customerID, dvdTitle});
    }

    inFile.close();
    std::cout << "\nRental history imported successfully.";
}
