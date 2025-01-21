#include "Header.hpp"

//NAME : NURUL AMIRAH BINTI MOHAMAD YUSOFF
//MATRIX NUMBER : 23301116
//FUNCTION : TO RETURN DVD

void returnDVD() {
    string customerID, customerName, findtitle, rentalperiod, Return, custID, line;
    string rentCustomerID, rentTitle, rentDate, returnDate, status;
    int rentalPeriod, daysLate;
    double difference;

    stringstream updatedContent;
    vector<string> rentHistoryReturn;
    bool recordFound = false, foundtitle = false;

    // Get customer ID and validate it
    if (!CustomerID(customerID, customerName)) {
        return;
    }

    cout << "\n-------------------" << "\nCustomer ID: " << customerID << "\nCustomer Name: " << customerName << "\n-------------------" << endl;

    // Display current rentals for the customer (only those that haven't been returned yet)
    ifstream infile("RentHistory.csv");
    if (!infile.is_open()) {
        cout << "ERROR" << endl;
        return;
    }

    cout << "\nCurrent Rentals:\n";
    while (getline(infile, Return)) {
    stringstream ss(Return);
    getline(ss, rentCustomerID, ',');
    getline(ss, customerName, ',');
    getline(ss, rentTitle, ',');
    getline(ss, rentDate, ',');
    getline(ss, returnDate, ',');
    getline(ss, status, ',');

    // Only display rentals where the return date is empty (i.e., not returned)
    if (rentCustomerID == customerID && returnDate.empty()) {
        cout << "Movie title: " << rentTitle << "\nRent Date: " << rentDate
             << "\nRental Period: " << status << "\n-------------------" << endl;
    }
    }
    infile.close();


    // Prompt user to enter the movie title
    cout << "What is the name of the movie: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer
    getline(cin, findtitle);  // Read movie title
    findtitle = normalizeString(findtitle);  // Normalize for consistent comparison

    // Open RentHistory.csv to find and update the return record
    infile.open("RentHistory.csv");
    if (!infile.is_open()) {
        cout << "ERROR" << endl;
        return;
    }

    while (getline(infile, Return)) {
        stringstream ss(Return);
        getline(ss, rentCustomerID, ',');
        getline(ss, customerName, ',');
        getline(ss, rentTitle, ',');
        getline(ss, rentDate, ',');
        getline(ss, returnDate, ',');
        getline(ss, status, ',');

        if (rentCustomerID == customerID && normalizeString(rentTitle) == findtitle && returnDate.empty()) {
            recordFound = true;

            // Parse the rent date
            struct tm tm_rentDate = {};
            stringstream rentDateStream(rentDate);
            rentDateStream >> get_time(&tm_rentDate, "%d/%m/%Y");

            // Get the current date
            time_t now = time(0);
            struct tm tm_now = *localtime(&now);

            // Calculate the difference in days
            time_t rentTimestamp = mktime(&tm_rentDate);
            time_t returnTimestamp = mktime(&tm_now);
            difference = difftime(returnTimestamp, rentTimestamp);
            daysLate = static_cast<int>(difference / (60 * 60 * 24));

            // Determine return status
            rentalPeriod = stoi(status);
            string returnStatus = (daysLate > rentalPeriod) ? "Late" : "On Time";

            // Update the return record
            returnDate = to_string(tm_now.tm_mday) + "/" + to_string(tm_now.tm_mon + 1) + "/" + to_string(tm_now.tm_year + 1900);
            Return = rentCustomerID + "," + customerName + "," + rentTitle + "," + rentDate + "," + returnDate + "," + status + "," + returnStatus;
        }

        rentHistoryReturn.push_back(Return);
    }
    infile.close();

    // Write updated rent history to file
    ofstream updatedRentHistory("RentHistory.csv", ios::out | ios::trunc);
    if (!updatedRentHistory.is_open()) {
        cout << "ERROR" << endl;
        return;
    }

    for (const auto& record : rentHistoryReturn) {
        updatedRentHistory << record << '\n';
    }
    updatedRentHistory.close();

    if (!recordFound) {
        cout << "No matching rental record found for '" << findtitle << "' and customer ID: " << customerID << "." << endl;
        return;
    } else {
        cout << "Return record updated successfully for '" << findtitle << "'." << endl;
    }

    // Open DVD_Rental_Database.csv and preserve the header
    ifstream dvdFile("DVD_Rental_Database.csv");
    if (!dvdFile.is_open()) {
        cout << "ERROR" << endl;
        return;
    }

    string header;
    getline(dvdFile, header);  // Read and store the header separately

    updatedContent << header << '\n';  // Add the header back to the updated content

    while (getline(dvdFile, line)) {
        stringstream ss(line);
        string title, genre, year;
        int stock;

        getline(ss, title, ',');
        getline(ss, genre, ',');
        getline(ss, year, ',');
        ss >> stock;

        if (normalizeString(title) == findtitle) {
            foundtitle = true;
            stock++;  // Increment the stock
        }

        updatedContent << title << "," << genre << "," << year << "," << stock << '\n';
    }
    dvdFile.close();

    if (!foundtitle) {
        cout << "Movie not found: " << findtitle << '\n';
        return;
    }

    // Write updated content back to DVD_Rental_Database.csv
    ofstream updatedDVDFile("DVD_Rental_Database.csv", ios::out | ios::trunc);
    if (!updatedDVDFile.is_open()) {
        cout << "ERROR" << endl;
        return;
    }

    updatedDVDFile << updatedContent.str();  // Write the entire updated content, including the header
    updatedDVDFile.close();

    cout << "The stock for '" << findtitle << "' has been updated." << endl;
}

// Utility Function: Normalize String
string normalizeString(const string& input) {
    string result = input;
    result.erase(result.find_last_not_of(" \n\r\t") + 1);  // Trim trailing spaces
    result.erase(0, result.find_first_not_of(" \n\r\t"));  // Trim leading spaces
    transform(result.begin(), result.end(), result.begin(), ::toupper);  // Convert to lowercase
    return result;
}
