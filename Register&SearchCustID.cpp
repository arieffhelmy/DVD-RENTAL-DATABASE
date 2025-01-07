#include "Header.hpp"

//NAME: TEEN JUN WEN
//MATRIX NUMBER: 23301879
//FUNCTION: TO REGISTER AND SERACH CUSTOMER ID

using namespace std;

unordered_map<string, Customer> customerDatabase;

string generateCustomerID() {
    static int idCounter = 1;
    stringstream ss;
    ss << "CUST" << idCounter++;
    return ss.str();
}

void toUpperCase(string &s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}

void exportToCSV(const vector<Customer>& customers) {
    ofstream file("customers.csv");
    file << "Name,Phone,Email,CustomerID\n";
    for (const auto& customer : customers) {
        file << customer.name << "," << customer.phone << "," << customer.email << "," << customer.customerID << "\n";
    }
    file.close();
    cout << "Customer data exported to customers.csv successfully.\n";
}

void registerCustomer() {
    Customer customer;
    cout << "Enter name (in uppercase): ";
    getline(cin, customer.name);
    toUpperCase(customer.name); // Convert name to uppercase
    cout << "Enter phone number: ";
    getline(cin, customer.phone);
    cout << "Enter email: ";
    getline(cin, customer.email);
    
    customer.customerID = generateCustomerID();
    customerDatabase[customer.customerID] = customer;
    
    cout << "Customer registered with ID: " << customer.customerID << "\n";
    
    // Automatically export to CSV after registration
    vector<Customer> customers;
    for (const auto& [id, customer] : customerDatabase) {
        customers.push_back(customer);
    }
    exportToCSV(customers);
}

void searchCustomer() {
    string searchParam;
    cout << "Enter name or phone number to search: ";
    getline(cin, searchParam);
    
    // Convert searchParam to uppercase for case-insensitive comparison
    toUpperCase(searchParam);

    bool found = false;
    for (const auto& [id, customer] : customerDatabase) {
        if (customer.name == searchParam || customer.phone == searchParam) {
            cout << "Customer ID: " << customer.customerID << "\n";
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "Customer not found.\n";
    }
}

