#include "Header.hpp"

//NAME: 
//MATRIX NUMBER: 
//FUNCTION: 


void AddDVDandStock()
{ 
    int choice;
    string line;
    vector<DVD> dvdCollection;
    DVD dvd;
    
    while (true) 
    {
        cout << "\n1. Add a new DVD\n";
        cout << "2. Add stock to an existing DVD\n";
        cout << "0. Return to main menu\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore();  // To ignore the newline left by cin
        
        if (choice == 0) {
            break;  // Exit the loop and return to the main menu
        }
        else if (choice == 1) {
        DVD dvd;
        ofstream output("DVD_Rental_Database.csv", ios::app);  // Open in append mode to add new records

            if (output.fail()) 
            {
                cout << "ERROR: Unable to open the file." << '\n';
                return;
            }

            // Collect DVD information from the user
            cout << "Enter the name of the movie: ";
            getline(cin, dvd.title);

            cout << "Enter the genre of the movie: ";
            getline(cin, dvd.genre);

            cout << "Enter the release year of the movie: ";
            getline(cin, dvd.year);

            cout << "Enter the number of stocks available: ";
            cin >> dvd.nostock;

            // Write the new DVD information to the file
            output << dvd.title << "," 
                << dvd.genre << "," 
                << dvd.year << "," 
                << dvd.nostock << endl;

            cout << "\nDVD added successfully!" << '\n';

            output.close();
        }
        else if (choice == 2) {
        // Read all DVDs into memory
        fstream inout;
        string header;

        inout.open("DVD_Rental_Database.csv", ios::in);
        if (inout.is_open()) 
        {
        getline(inout, header);

        while (getline(inout, line)) {
            stringstream ss(line);
            getline(ss, dvd.title, ',');
            getline(ss, dvd.genre, ',');
            getline(ss, dvd.year, ',');
            ss >> dvd.nostock;
            dvdCollection.push_back(dvd);
        }
        inout.close();


        } else {
            cout << "ERROR: Unable to open the file." << '\n';
            continue;
        }
        // Add stock to an existing DVD
            cout << "Enter the name of the movie: ";
            getline(cin, dvd.title);

            cout << "Enter the genre of the movie: ";
            getline(cin, dvd.genre);

            cout << "Enter the release year of the movie: ";
            getline(cin, dvd.year);

            cout << "Enter the number of stocks to add: ";
            cin >> dvd.nostock;
            cin.ignore();  // To ignore the newline left by cin

        bool founddvd = false;

        // Search for the DVD by title
            for (auto& existingDVD : dvdCollection) {
                if (existingDVD.title == dvd.title && existingDVD.genre == dvd.genre && existingDVD.year == dvd.year) {
                    founddvd = true;
                    existingDVD.nostock += dvd.nostock;
                    break;
                }
        }

        if (!founddvd) {
            cout << "DVD not found in the database!" << endl;
            continue;
        }

        // Write the updated DVD list back to the file
        inout.open("DVD_Rental_Database.csv", ios::out | ios::trunc);

        if (inout.fail()) {
            cout << "ERROR: Unable to open the file." << '\n';
            continue;
        }
        inout << header << "\n";

        for (const auto& existingDVD : dvdCollection) {
            inout << existingDVD.title << ","
                << existingDVD.genre << ","
                << existingDVD.year << ","
                << existingDVD.nostock << endl;
        }

        cout << "\nStock added successfully!" << '\n';
        inout.close();
    }
        else {
            cout << "Invalid choice. Please select 0, 1, or 2." << endl;
        }
    }
}
