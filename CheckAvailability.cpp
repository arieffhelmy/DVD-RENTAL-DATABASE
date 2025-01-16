#include "Header.hpp"

//NAME: MUHAMMAD ARIEFF BIN HELMY SHAM
//MATRIX NUMBER: 23303466
//FUNCTION: TO CHECK THE AVAILABILITY OF DVD BY SEARCHING SPECIFIC GENRE

void CheckAvailability() {
    vector<DVD> dvdCollection;

    DVD dvd;

    string findgenre, findtitle;
    string top;

    ifstream file("DVD_Rental_Database.csv");

    if (file.fail()) {
        cout << "ERROR: Unable to open the file." << '\n';
        return;
    }

    // Skip the header row (if present)
    getline(file, top);

    // Populate dvdCollection by reading the file
    while (getline(file, top)) {
        stringstream ss(top);
        
        // Assuming the CSV has columns: Title, Genre, Year, Stock
        getline(ss, dvd.title, ',');
        getline(ss, dvd.genre, ',');
        getline(ss, dvd.year, ',');
        ss >> dvd.nostock;

        dvdCollection.push_back(dvd);
    }

    cout << "What is the name of the movie: ";
    getline(cin, findtitle);

    bool foundtitle = false;

    // Searching by title
    for (const auto& dvd : dvdCollection) {
        if (findtitle == dvd.title) {
            foundtitle = true;
            cout << "\nName: " << dvd.title << '\n';
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
        cout << "What is the genre of the movie (Action, Fantasy, Romance, Horror, Comedy): ";
        cin >> findgenre;

        bool foundgenre = false;

        // Searching by genre
        for (const auto& dvd : dvdCollection) {
            if (findgenre == dvd.genre) {
                foundgenre = true;
                cout << "\nName: " << dvd.title << '\n';
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

    file.close();
}
