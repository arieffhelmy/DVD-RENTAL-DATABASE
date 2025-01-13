#include "Header.hpp"

//NAME: TEEN JUN WEN
//MATRIX NUMBER: 23301879
//FUNCTION: TO REGISTER AND SERACH CUSTOMER ID

void toUpperCase(string &s) 
{
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}

string generateCustomerID() {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(0)));

    // Generate a random number in the range [1000, 9999]
    int randomNumber = rand() % 9000 + 1000;

    stringstream ss;
    ss << "CUST" << randomNumber;  // Append the random number to "CUST"
    return ss.str();
}

void registerCustomer()
{
    Customer customer;
    ofstream op("customer.csv", ios::app);
    if (!op.is_open()) 
    {
        cout << "ERROR: Unable to open the file." << endl;
        return;
    }

    cout << "Enter name (in uppercase): ";
    getline(cin, customer.name);
    toUpperCase(customer.name);

    cout << "Enter phone number: ";
    getline(cin, customer.phone);

    cout << "Enter email: ";
    getline(cin, customer.email);

    customer.customerID = generateCustomerID();

    op << customer.name << "," << customer.phone << "," << customer.email << "," << customer.customerID << endl;
    cout << "Customer registered with ID: " << customer.customerID << endl;

    op.close();
}


void searchCustomer() 
{
    vector<Customer> CustomerID;
    ifstream ip("customer.csv");

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

    cout << "What is your name? > ";
    getline(cin, findname);
    toUpperCase(findname);

    bool foundname = false;

    for (const auto& customer : CustomerID) 
    {
        if (findname == customer.name) 
        {
            foundname = true;
            cout << "Name: " << customer.name << endl;
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