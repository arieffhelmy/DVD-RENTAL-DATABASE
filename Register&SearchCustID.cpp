#include "Header.hpp"

//NAME: TEEN JUN WEN
//MATRIX NUMBER: 23301879
//FUNCTION: TO REGISTER A NEW CUSTOMER, TO SEARCH CUSTOMER ID AND TO GENERATE CUSTOMER ID


//FUNCTION : TO REGISTER A NEW CUSTOMER
void registerCustomer()
{
    vector<Customer> customers;

    customers.clear();

    ifstream ip("DATA/customers.csv");

    if (!ip.is_open()) 
    {
        cout << "ERROR: Unable to open the file for reading." << endl;
        return;
    }

    Customer customer;
    string line;

    while (getline(ip, line))
    {
        stringstream ss(line);
        getline(ss, customer.name, ',');
        getline(ss, customer.phone, ',');
        getline(ss, customer.email, ',');
        getline(ss, customer.customerID);
        customers.push_back(customer);
    }
    ip.close();

    cout << "Enter name (in uppercase): ";
    getline(cin, customer.name);
    normalizeString(customer.name);

    cout << "Enter phone number: ";
    getline(cin, customer.phone);

    cout << "Enter email: ";
    getline(cin, customer.email);

    transform(customer.email.begin(), customer.email.end(), customer.email.begin(), ::tolower);

    customer.customerID = generateCustomerID();

    // Check if the customer already exists
    for (const auto& existingCustomer : customers)
    {
        if (existingCustomer.phone == customer.phone || existingCustomer.email == customer.email)
        {
            cout << "ERROR: A customer with this phone number or email already exists." << endl;
            return;
        }
    }

    customers.push_back(customer);

    cout << "Customer registered with ID: " << customer.customerID << endl;

    ofstream op("DATA/customers.csv");

    if (!op.is_open()) 
    {
        cout << "ERROR: Unable to open the file for writing." << endl;
        return;
    }
    
    for (const auto& c : customers)
    {
        op << normalizeString(c.name) << "," 
           << c.phone << "," 
           << c.email << "," 
           << c.customerID << endl;
    }    
    op.close();
}


//FUNCTION : TO SEARCH CUSTOMER ID
void searchCustomer() 
{
    vector<Customer> CustomerID;
    vector<Customer> customers;

    string line,findname, findphone;
    ifstream ip("DATA/customers.csv");

    if (!ip.is_open()) 
    {
        cout << "ERROR: Unable to open the file." << endl;
        return;
    }


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

    cout << "Enter Customer name : ";
    getline(cin, findname);

    bool foundname = false;

    for (const auto& customer : CustomerID) 
    {
        if (normalizeString(findname) == normalizeString(customer.name)) 
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

        cout << "Enter Phone number: ";
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


//FUNCTION : TO GENERATE CUSTOMER ID
string generateCustomerID() 
{
    vector<Customer> customers;

    // Start from "CUST1" if no customers exist
    if (customers.empty()) 
    {
        return "CUST1";  
    }

    string latestCustomerID = customers.back().customerID;

    // Ensure that the ID has the correct format
    if (latestCustomerID.substr(0, 4) == "CUST") 
    {
        try 
        {
            int customerid = stoi(latestCustomerID.substr(4)); 
            
            return "CUST" + to_string(customerid + 1);
        } catch (const std::invalid_argument& e) 
        {
            cout << "Error: Invalid customer ID format" << endl;
            return "CUST1"; 
        }
    }
    return "CUST1";
}