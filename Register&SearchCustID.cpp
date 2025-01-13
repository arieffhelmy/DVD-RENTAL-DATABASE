#include "Header.hpp"

//NAME: TEEN JUN WEN
//MATRIX NUMBER: 23301879
//FUNCTION: TO REGISTER AND SERACH CUSTOMER ID

void toUpperCase(string &s);
string generateCustomerID();
vector<Customer> customers;

void toUpperCase(string &s) 
{
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}

string generateCustomerID() {
    if (customers.empty()) {
        return "CUST1";  // Start from "CUST1" if no customers exist
    }

    // Get the last customer ID
    string latestCustomerID = customers.back().customerID;

    // Ensure that the ID has the correct format (i.e., starts with "CUST")
    if (latestCustomerID.substr(0, 4) == "CUST") {
        try {
            int customerid = stoi(latestCustomerID.substr(4));  // Extract the numeric part of the ID
            
            return "CUST" + to_string(customerid + 1);  // Increment the ID
        } catch (const std::invalid_argument& e) {
            // Handle case where the conversion fails
            cout << "Error: Invalid customer ID format" << endl;
            return "CUST1";  // Default to "CUST1" in case of an invalid ID format
        }
    }
    return "CUST1";
}


void registerCustomer()
{
    ifstream ip("customers.csv");  // Open the file to read existing customers
    if (!ip.is_open()) 
    {
        cout << "ERROR: Unable to open the file." << endl;
        return;
    }

    // Read existing customers from the file into the vector
    Customer customer;
    while (getline(ip, customer.name, ',') &&
           getline(ip, customer.phone, ',') &&
           getline(ip, customer.email, ',') &&
           getline(ip, customer.customerID))
    {
        customers.push_back(customer);
    }
    ip.close();  // Close the file after reading existing customers

    // Collect new customer details
    cout << "Enter name (in uppercase): ";
    getline(cin, customer.name);
    toUpperCase(customer.name);

    cout << "Enter phone number: ";
    getline(cin, customer.phone);

    cout << "Enter email: ";
    getline(cin, customer.email);

    customer.customerID = generateCustomerID();

    // Check if the customer already exists (based on phone number or email)
    for (const auto& existingCustomer : customers)
    {
        if (existingCustomer.phone == customer.phone || existingCustomer.email == customer.email)
        {
            cout << "ERROR: A customer with this phone number or email already exists." << endl;
            return;
        }
    }

    // Confirm registration
    cout << "Customer registered with ID: " << customer.customerID << endl;

    // Write the new customer to the file
    ofstream op("customers.csv", ios::app); // Open the file in append mode
    if (!op.is_open()) 
    {
        cout << "ERROR: Unable to open the file." << endl;
        return;
    }
    
    op << customer.name << "," 
       << customer.phone << "," 
       << customer.email << "," 
       << customer.customerID << endl;
    
    op.close();  // Close the file
}



void searchCustomer() 
{
    vector<Customer> CustomerID;
    ifstream ip("customers.csv");

    if (!ip.is_open()) 
    {
        cout << "ERROR: Unable to open the file." << endl;
        return;
    }

    string line;
    getline(ip, line);

    while (getline(ip, line)) 
    {
        stringstream ss(line);
        Customer customer;

        getline(ss, customer.name, ',');
        getline(ss, customer.phone, ',');
        getline(ss, customer.email, ',');
        ss >> customer.customerID;

        CustomerID.push_back(customer);
    }

    string findname, findphone;

    cout << "What is customer name? > ";
    getline(cin, findname);
    toUpperCase(findname);

    bool foundname = false;

    for (const auto& customer : CustomerID) 
    {
        if (findname == customer.name) 
        {
            foundname = true;
            cout << "\nName: " << customer.name << endl;
            cout << "Phone Number: " << customer.phone << endl;
            cout << "Email: " << customer.email << endl;
            cout << "Customer ID: " << customer.customerID << endl;
            cout << "-------------------" << endl;
        }
    }

    if (!foundname) 
    {
        cout << "This name is not found: " << findname << endl;
        cout << "You can try by searching with phone number." << endl;

        cout << "What is the your phone number? > ";
        cin >> findphone;

    bool foundphone = false;

    for (const auto& customer : CustomerID) 
    {
        if (findphone == customer.phone) 
        {
            foundphone = true;
            cout << "Name: " << customer.name << endl;
            cout << "Phone Number: " << customer.phone << endl;
            cout << "Email: " << customer.email << endl;
            cout << "Customer ID: " << customer.customerID << endl;
            cout << "-------------------" << endl;
        }
    }

    if (!foundphone) 
    {
        cout << "This name is not yet registered: " << findname << endl;
        cout << "You can try by register a new customer ID." << endl;
    }
    }

    ip.close();
}