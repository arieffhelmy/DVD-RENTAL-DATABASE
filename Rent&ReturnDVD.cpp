#include "Header.hpp"

//NAME : LAI YIN YI
//MATRIX NUMBER : 23304223
//FUNCTION : TO RENT DVD

//NAME : NURUL AMIRAH BINTI MOHAMAD YUSOFF
//MATRIX NUMBER : 23301116
//FUNCTION : TO RETURN DVD

bool CustomerID(string& customerID, string& customerName);

void rentDVD() {
    string customerID, customerName;
    vector<DVD> dvdCollection;
    vector<Customer> customers;
    DVD dvd;
    Rental rental;
    string findtitle;
    string line;
    int rentalPeriod; // Rental period (in days)

    // Get customer ID and validate it
    if (!CustomerID(customerID, customerName)) {
        cout << "Cannot proceed with DVD rental due to invalid customer ID." << endl;
        return;
    }

    // Read DVD data from file
    fstream file("DVD_Rental_Database.csv", ios::in);
    if (!file.is_open()) {
        cout << "ERROR: Unable to open DVD_Rental_Database.csv." << '\n';
        return;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, dvd.title, ',');
        getline(ss, dvd.genre, ',');
        getline(ss, dvd.year, ',');
        ss >> dvd.nostock;
        dvdCollection.push_back(dvd);
    }
    file.close();

    // Get movie title from user
    cout << "What is the name of the movie: ";
    cin.ignore(); // Ignore newline character
    getline(cin, findtitle);

    bool foundtitle = false;

    // Find and rent the movie
    for (auto& d : dvdCollection) {
        if (findtitle == d.title) {
            foundtitle = true;
            if (d.nostock > 0) { // Check if stock is available
                d.nostock--;
            } else {
                cout << "Movie '" << findtitle << "' is currently out of stock." << endl;
                return;
            }
            break;
        }
    }

    if (!foundtitle) {
        cout << "Movie not found: " << findtitle << '\n';
        return;
    } else {
        cout << "The stock for '" << findtitle << "' has been updated." << '\n';
    }

    // Get rental period (number of days to rent the movie)
    cout << "How many days would you like to rent the movie? ";
    cin >> rentalPeriod;

    // Update DVD_Rental_Database.csv
    file.open("DVD_Rental_Database.csv", ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "ERROR: Unable to open DVD_Rental_Database.csv for writing." << '\n';
        return;
    }

    for (const auto& d : dvdCollection) {
        file << d.title << ',' << d.genre << ',' << d.year << ',' << d.nostock << '\n';
    }
    file.close();

    // Record rental in RentHistory.csv (including rental period and rental date)
    ofstream op("RentHistory.csv", ios::app);

    // Debugging: Print details before writing
    cout << "\n\nCustomerID: " << customerID << '\n'
         << "CustomerName: " << customerName << '\n'
         << "Title: " << findtitle << '\n'
         << "Rental Date: " << rental.dates << '\n'
         << "Rental Period: " << rentalPeriod << " days" << endl;

    if (op.is_open()) {
        op << customerID << "," << customerName << "," << findtitle << "," << rental.dates << "," << "," << rentalPeriod << endl;  // Leave return date empty for now
        
        cout << "Data written to RentHistory.csv successfully." << endl;
    } else {
        cout << "Error opening RentHistory.csv." << endl;
    }

    op.close();
}

void returnDVD() {
    string customerID, customerName, findtitle, rentalperiod;
    vector<DVD> dvdCollection;
    vector<string> rentHistoryLines;
    Rental rental;
    string line;
    bool recordFound = false;

    // Get customer ID and validate it
    if (!CustomerID(customerID, customerName)) {
        cout << "Cannot proceed with DVD return due to invalid customer ID." << endl;
        return;
    }

    // Read DVD data from file
    fstream file("DVD_Rental_Database.csv", ios::in);
    if (!file.is_open()) {
        cout << "ERROR: Unable to open DVD_Rental_Database.csv." << '\n';
        return;
    }

    DVD dvd;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, dvd.title, ',');
        getline(ss, dvd.genre, ',');
        getline(ss, dvd.year, ',');
        ss >> dvd.nostock;
        dvdCollection.push_back(dvd);
    }
    file.close();

    // Get movie title from user
    cout << "What is the name of the movie: ";
    cin.ignore(); // Ignore newline character
    getline(cin, findtitle);

    bool foundtitle = false;

    // Find the movie to return
    for (auto& d : dvdCollection) {
        if (findtitle == d.title) {
            foundtitle = true;
            d.nostock++; // Increment stock
            break;
        }
    }

    if (!foundtitle) {
        cout << "Movie not found: " << findtitle << '\n';
        return;
    } else {
        cout << "The stock for '" << findtitle << "' has been updated." << '\n';
    }

    // Update DVD_Rental_Database.csv
    file.open("DVD_Rental_Database.csv", ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "ERROR: Unable to open DVD_Rental_Database.csv for writing." << '\n';
        return;
    }

    for (const auto& d : dvdCollection) {
        file << d.title << ',' << d.genre << ',' << d.year << ',' << d.nostock << '\n';
    }
    file.close();

    // Process RentHistory.csv to update the record
    fstream rentHistory("RentHistory.csv", ios::in);
    if (!rentHistory.is_open()) {
        cout << "ERROR: Unable to open RentHistory.csv." << endl;
        return;
    }

    while (getline(rentHistory, line)) {
        stringstream ss(line);
        string rentCustomerID, rentTitle, rentDate, returnDate, status;

        getline(ss, rentCustomerID, ',');
        getline(ss, customerName, ',');
        getline(ss, rentTitle, ',');
        getline(ss, rentDate, ',');
        getline(ss, returnDate, ',');
        getline(ss, status, ',');  // Get rental period (status)

        if (rentCustomerID == customerID && rentTitle == findtitle && returnDate.empty()) {
            recordFound = true;

            // Manually parse rentDate into tm structure
            struct tm tm_rentDate = {};
            stringstream rentDateStream(rentDate);
            rentDateStream >> get_time(&tm_rentDate, "%Y-%m-%d");  // Parsing date format (YYYY-MM-DD)

            // Get the current date
            time_t now = time(0);
            struct tm tm_now = *localtime(&now);

            // Calculate the difference in days between current date and rentDate
            time_t rentTimestamp = mktime(&tm_rentDate);
            time_t returnTimestamp = mktime(&tm_now);

            double difference = difftime(returnTimestamp, rentTimestamp); // Calculate the time difference
            int daysLate = static_cast<int>(difference / (60 * 60 * 24)); // Convert time difference to days, and cast to int
            
            // Check if 'status' contains valid numeric data (rental period)
            int rentalPeriod = 0;
            try {
                rentalPeriod = stoi(status); // Try converting status to int
            } catch (const std::invalid_argument& e) {
                cout << "Error: Invalid rental period (status) format: " << status << ". " << e.what() << endl;
                continue; // Skip this record if stoi throws an exception
            } catch (const std::out_of_range& e) {
                cout << "Error: Rental period (status) is out of range: " << status << ". " << e.what() << endl;
                continue; // Skip this record if stoi throws an out-of-range exception
            }

            // Determine if the return is late or in time
            string returnStatus = (daysLate > rentalPeriod) ? "Late" : "In Time";

            // Update the row with return date and status
            rentalperiod = to_string(rentalPeriod);
            line = rentCustomerID + "," + customerName + "," + rentTitle + "," + rentDate + "," + rental.dates + "," + rentalperiod + "," + returnStatus;
        }

        rentHistoryLines.push_back(line);
    }
    rentHistory.close();

    // Write updated data back to RentHistory.csv
    ofstream updatedRentHistory("RentHistory.csv", ios::out | ios::trunc);
    if (!updatedRentHistory.is_open()) {
        cout << "ERROR: Unable to open RentHistory.csv for writing." << endl;
        return;
    }

    for (const auto& record : rentHistoryLines) {
        updatedRentHistory << record << '\n';
    }

    updatedRentHistory.close();

    if (recordFound) {
        cout << "Return record updated successfully for '" << findtitle << "'." << endl;
    } else {
        cout << "No matching rental record found for '" << findtitle << "' and customer ID: " << customerID << "." << endl;
    }
}


// CustomerID function to verify customer
bool CustomerID(string& customerID, string& customerName) {
    vector<Customer> customers;
    Customer customer;
    string findcustomerID, line;

    // Open the file for both reading and writing
    fstream file("customers.csv", ios::in | ios::out);

    if (!file.is_open()) {
        cout << "ERROR: Unable to open the file." << '\n';
        return false;
    }

    bool foundcustomerID = false;

    cout << "Enter customer ID: ";
    cin >> findcustomerID;

    // Read each line from the file
    while (getline(file, line)) {
        stringstream ss(line); // Use stringstream to split the line by commas
        
        // Parse the fields using getline with the delimiter ','
        getline(ss, customer.name, ',');
        getline(ss, customer.phone, ',');
        getline(ss, customer.email, ',');
        getline(ss, customer.customerID, ',');

        // Check if the customerID matches
        if (findcustomerID == customer.customerID) {
            foundcustomerID = true;
            customerID = findcustomerID; // Update customerID
            customerName = customer.name; // Update customerName
            cout << "Name: " << customer.name << '\n';
            cout << "Phone: " << customer.phone << '\n';
            cout << "Email: " << customer.email << '\n';
            break;
        }
    }

    // If the customer was not found
    if (!foundcustomerID) {
        cout << "Invalid customer ID" << endl;
    }
    file.close();
    return foundcustomerID;
}
