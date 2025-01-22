#include "Header.hpp"

//NAME : NURUL AMIRAH BINTI MOHAMAD YUSOFF
//MATRIX NUMBER : 23301116
//FUNCTION : TO RETURN DVD AND TO NORMALIZE STRING BECOMES UPPERCASE

//FUNCTION : TO RETURN DVD
void returnDVD() {
    string customerID, customerName, findtitle, rentalperiod, Return, custID, line;
    string rentCustomerID, rentTitle, rentDate, returnDate, status;
    int rentalPeriod, daysLate;
    double difference;

    stringstream updatedContent;
    vector<string> rentHistoryReturn;
    bool recordFound = false, foundtitle = false;

    if (!CustomerID(customerID, customerName)) {
        return;
    }

    cout << "\n-------------------";
    cout << "\nCustomer ID: " << customerID;
    cout << "\nCustomer Name: " << customerName;
    cout  << "\n-------------------" << endl;

    // Display current rentals for the customer for those that haven't returned the dvd yet
    ifstream infile("RentHistory.csv");
    
    if (!infile.is_open()) 
    {
        cout << "ERROR" << endl;
        return;
    }

    cout << "\nCurrent Rentals:\n\n";

    bool currentrentals = false;

    while (getline(infile, Return)) 
    {
        stringstream ss(Return);
        getline(ss, rentCustomerID, ',');
        getline(ss, customerName, ',');
        getline(ss, rentTitle, ',');
        getline(ss, rentDate, ',');
        getline(ss, returnDate, ',');
        getline(ss, status, ',');

        // Only display rentals where the return date is empty
        if (rentCustomerID == normalizeString(customerID) && returnDate.empty()) 
        {
            currentrentals = true;
            
            cout << "Movie title: " << rentTitle;
            cout << "\nRent Date: " << rentDate;
            cout << "\nRental Period: " << status;
            cout << "\n-------------------" << endl;
        }
    }

    if (!currentrentals)
    {
        cout << "No current rentals for this customer ID." << endl;
        return;
    }
    infile.close();


    cout << "What is the name of the movie: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    getline(cin, findtitle); 

    infile.open("RentHistory.csv");
    if (!infile.is_open()) {
        cout << "ERROR" << endl;
        return;
    }

    while (getline(infile, Return)) 
    {
        stringstream ss(Return);
        getline(ss, rentCustomerID, ',');
        getline(ss, customerName, ',');
        getline(ss, rentTitle, ',');
        getline(ss, rentDate, ',');
        getline(ss, returnDate, ',');
        getline(ss, status, ',');

        //To determine the return status and update return date
        if (rentCustomerID == normalizeString(customerID) && normalizeString(rentTitle) == normalizeString(findtitle) && returnDate.empty()) {
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

    ofstream updatedRentHistory("RentHistory.csv", ios::out | ios::trunc);
    if (!updatedRentHistory.is_open()) 
    {
        cout << "ERROR" << endl;
        return;
    }

    for (const auto& record : rentHistoryReturn) 
    {
        updatedRentHistory << record << '\n';
    }
    updatedRentHistory.close();

    if (!recordFound) 
    {
        cout << "\nNo matching rental record found for '" << findtitle << "' and customer ID: " << customerID << "." << endl;
        return;
    } 
    else 
    {
        cout << "\nReturn record updated successfully for '" << findtitle << "'." << endl;
    }

    
    ifstream dvdFile("DVD_Rental_Database.csv");
    
    if (!dvdFile.is_open()) 
    {
        cout << "ERROR" << endl;
        return;
    }

    string header;

    getline(dvdFile, header);  

    updatedContent << header << '\n';  

    while (getline(dvdFile, line)) 
    {
        stringstream ss(line);
        string title, genre, year;
        int stock;

        getline(ss, title, ',');
        getline(ss, genre, ',');
        getline(ss, year, ',');
        ss >> stock;

        if (normalizeString(title) == normalizeString(findtitle)) 
        {
            foundtitle = true;
            stock++;  
        }

        updatedContent << title << "," << genre << "," << year << "," << stock << '\n';
    }
    dvdFile.close();

    if (!foundtitle) 
    {
        cout << "Movie not found: " << findtitle << '\n';
        return;
    }


    ofstream updatedDVDFile("DVD_Rental_Database.csv", ios::out | ios::trunc);
    if (!updatedDVDFile.is_open()) 
    {
        cout << "ERROR" << endl;
        return;
    }

    updatedDVDFile << updatedContent.str(); 
    updatedDVDFile.close();

    cout << "The stock for " << findtitle << " has been updated." << endl;
}


//FUNCTION : TO NORMALIZE STRING BECOMES UPPERCASE
string normalizeString(const string& input) 
{
    string result = input;
    result.erase(result.find_last_not_of(" \n\r\t") + 1);  //trim
    result.erase(0, result.find_first_not_of(" \n\r\t"));  //trim
    transform(result.begin(), result.end(), result.begin(), ::toupper);  
    return result;
}
