#include "Header.hpp"

//NAME: MUHAMMAD ARIEFF BIN HELMY SHAM
//MATRIX NUMBER: 23303466
//FUNCTION: TO CHECK THE AVAILABILITY OF DVD BY SEARCHING SPECIFIC GENRE


void CheckAvailability() 
{
    vector<DVD> dvdCollection;

    DVD dvd;

    string genre, title;
    string top;

    ifstream file("DATA/DVD_Rental_Database.csv");

    if (file.fail()) 
    {
        cout << "ERROR: Unable to open the file." << '\n';
        return;
    }

    getline(file, top);

    while (getline(file, top)) 
    {
        stringstream ss(top);
        
        getline(ss, dvd.title, ',');
        getline(ss, dvd.genre, ',');
        getline(ss, dvd.year, ',');
        ss >> dvd.nostock;

        dvdCollection.push_back(dvd);
    }

    cout << "What is the name of the movie: ";
    getline(cin, title);

    bool foundtitle = false;

    // Searching by title
    for (const auto& dvd : dvdCollection) 
    {
        if (normalizeString(title) == normalizeString(dvd.title)) 
        {
            foundtitle = true;
            cout << "\nName: " << dvd.title << '\n';
            cout << "Genre: " << dvd.genre << '\n';
            cout << "Released Year: " << dvd.year << '\n';
            cout << "No of Stocks: " << dvd.nostock << '\n';
            cout << "-------------------" << '\n';
        }
    }

    if (!foundtitle) 
    {
        cout << "No movies found for the title: " << title << '\n';
        cout << "You can try by finding a specific genre. \n\n";

        cout << "What is the genre of the movie (Action, Drama, Fantasy, Romance, Horror, Comedy): ";
        cin >> genre;
        genre = normalizeString(genre); 

        bool foundgenre = false;

        // Searching by genre
        for (const auto& dvd : dvdCollection) 
        {
            if (genre == normalizeString(dvd.genre)) 
            {
                foundgenre = true;
                cout << "\nName: " << dvd.title << '\n';
                cout << "Genre: " << dvd.genre << '\n';
                cout << "Released Year: " << dvd.year << '\n';
                cout << "No of Stocks: " << dvd.nostock << '\n';
                cout << "-------------------" << '\n';
            }
        }

        if (!foundgenre) 
        {
            cout << "No movies found for the genre: " << genre << '\n';
        }
    }

    file.close();
}
