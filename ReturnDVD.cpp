#include "Header.hpp"

//NAME : NURUL AMIRAH BINTI MOHAMAD YUSOFF
//MATRIX NUMBER : 23301116
//FUNCTION : TO RETURN DVD

void returnDVD() {
    string customerID, customerName, findtitle, rentalperiod, Return, custID;
    string rentCustomerID, rentTitle, rentDate, returnDate, returnStatus, status;
    string title, genre, year;
    int nostock;
    double difference;
    int daysLate, rentalPeriod;

    vector<DVD> dvdCollection;
    vector<string> rentHistoryReturn;
    vector<Rental> rentalHistory;

    bool recordFound = false;
    bool foundtitle = false;

    // Get customer ID and validate it
    if (!CustomerID(customerID, customerName)) {
        cout << "Cannot proceed with DVD return due to invalid customer ID." << endl;
        return;
    }

// Read what movie customer rent at the moment from file
ifstream infile("RentHistory.csv");
if (infile.fail()) {
    cout << "ERROR: Unable to open RentHistory.csv." << '\n';
    return;
}

while (getline(infile, Return)) {
    stringstream ss(Return);

    Customer customer;  
    DVD dvd;            
    Rental rental;      

    // Extract customer details
    getline(ss, customer.customerID, ',');
    getline(ss, customer.name, ',');

    // Extract rental details
    getline(ss, dvd.title, ',');
    getline(ss, rental.rentdate, ',');
    getline(ss, rental.returndate, ',');
    ss >> rental.rentalPeriod;

    // Add to respective vectors
    rentalHistory.push_back(rental);
    customers.push_back(customer);
    dvdCollection.push_back(dvd);
}

bool foundID = false;

// Searching by ID
for (size_t i = 0; i < customers.size(); ++i) {
    if (customerID == customers[i].customerID) {
        foundID = true;

        cout << "\nCustomer ID: " << customers[i].customerID << '\n';
        cout << "Customer Name: " << customers[i].name << '\n';
        cout << "Movie title: " << dvdCollection[i].title << '\n';
        cout << "Rent Date: " << rentalHistory[i].rentdate << '\n';
        cout << "Rental Period: " << rentalHistory[i].rentalPeriod << '\n';
        cout << "-------------------" << '\n';
        }
}

if (!foundID) {
    cout << "Data not found\n";
}

infile.close();


    // Read DVD data from file
    fstream read("DVD_Rental_Database.csv", ios::in);
    if (read.fail()) {
        cout << "ERROR: Unable to open DVD_Rental_Database.csv." << '\n';
        return;
    }
 
    while (getline(read, Return)) {
        stringstream ss(Return);

        DVD dvd;

        getline(ss, title, ',');
        getline(ss, genre, ',');
        getline(ss, year, ',');
        ss >> nostock;
        dvdCollection.push_back(dvd);
    }
    read.close();

    // Get movie title from user
    cout << "What is the name of the movie: ";
    cin.ignore(); // Ignore newline character
    getline(cin, findtitle);    

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
    fstream file;

    file.open("DVD_Rental_Database.csv", ios::out | ios::trunc);
    if (file.fail()) {
        cout << "ERROR: Unable to open DVD_Rental_Database.csv for writing." << '\n';
        return;
    }

    for (const auto& d : dvdCollection) {
        file << d.title << ',' << d.genre << ',' << d.year << ',' << d.nostock << '\n';
    }
    file.close();

    // Process RentHistory.csv to update the record
    fstream rentHistory("RentHistory.csv", ios::in);
    if (rentHistory.fail()) {
        cout << "ERROR: Unable to open RentHistory.csv." << endl;
        return;
    }

    while (getline(rentHistory, Return)) {
        stringstream ss(Return);

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

            difference = difftime(returnTimestamp, rentTimestamp); // Calculate the time difference
            daysLate = static_cast<int>(difference / (60 * 60 * 24)); // Convert time difference to days, and cast to int
            
            // Check if 'status' contains valid numeric data (rental period)
            rentalPeriod = 0;
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
            returnStatus = (daysLate > rentalPeriod) ? "Late" : "On Time";

            // Update the row with return date and status
            rentalperiod = to_string(rentalPeriod);

            Rental rental;

            Return = rentCustomerID + "," + customerName + "," + rentTitle + "," + rentDate + "," + rental.returndate + "," + rentalperiod + "," + returnStatus;
        }

        rentHistoryReturn.push_back(Return);
    }
    rentHistory.close();

    // Write updated data back to RentHistory.csv
    ofstream updatedRentHistory("RentHistory.csv", ios::out | ios::trunc);
    if (updatedRentHistory.fail()) {
        cout << "ERROR: Unable to open RentHistory.csv for writing." << endl;
        return;
    }

    for (const auto& record : rentHistoryReturn) {
        updatedRentHistory << record << '\n';
    }

    updatedRentHistory.close();

    if (recordFound) {
        cout << "Return record updated successfully for '" << findtitle << "'." << endl;
    } else {
        cout << "No matching rental record found for '" << findtitle << "' and customer ID: " << customerID << "." << endl;
    }
}