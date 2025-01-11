#include "Header.hpp"

//NAME: MUHAMMAD ARIEFF BIN HELMY SHAM
//MATRIX NUMBER: 23303466
//FUNCTION: TO CHECK THE AVAILABILITY OF DVD BY SEARCHING SPECIFIC GENRE

vector<DVD> dvdCollection;

void CheckAvailability() {
    ifstream ip("DVD_Rental_Database.csv");

    if (!ip.is_open()) {
        cout << "ERROR: Unable to open the file." << '\n';
        return;
    }

    string line;
    // Skip the header row (if present)
    getline(ip, line);

    // Populate dvdCollection by reading the file
    while (getline(ip, line)) {
        stringstream ss(line);
        DVD dvd;

        // Assuming the CSV has columns: Title, Genre, Year, Stock
        getline(ss, dvd.title, ',');
        getline(ss, dvd.genre, ',');
        ss >> dvd.year;
        ss.ignore(1, ','); // Skip the comma after the year
        ss >> dvd.nostock;

        dvdCollection.push_back(dvd);
    }

    string findgenre, findtitle;

    cout << "What is the name of the movie: ";
    getline(cin, findtitle);

    bool foundtitle = false;

    // Searching by title
    for (const auto& dvd : dvdCollection) {
        if (findtitle == dvd.title) {
            foundtitle = true;
            cout << "Name: " << dvd.title << '\n';
            cout << "Genre: " << dvd.genre << '\n';
            cout << "Released Year: " << dvd.year << '\n';
            cout << "No of Stocks: " << dvd.nostock << '\n';
            cout << "-------------------" << '\n';
        }
    }

    if (!foundtitle) {
        cout << "No movies found for the title: " << findtitle << '\n';
        cout << "You can try by finding a specific genre. \n\n";

        // Ask for genre if title not found
        cout << "What is the genre of the movie: ";
        cin >> findgenre;

        bool foundgenre = false;

        // Searching by genre
        for (const auto& dvd : dvdCollection) {
            if (findgenre == dvd.genre) {
                foundgenre = true;
                cout << "Name: " << dvd.title << '\n';
                cout << "Genre: " << dvd.genre << '\n';
                cout << "Released Year: " << dvd.year << '\n';
                cout << "No of Stocks: " << dvd.nostock << '\n';
                cout << "-------------------" << '\n';
            }
        }

        if (!foundgenre) {
            cout << "No movies found for the genre: " << findgenre << '\n';
        }
    }

    ip.close();
}
