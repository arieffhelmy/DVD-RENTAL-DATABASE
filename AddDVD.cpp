#include "Header.hpp"

//NAME: MUHAMMAD ARIEFF BIN HELMY SHAM
//MATRIX NUMBER: 23303466
//FUNCTION: TO CHECK THE AVAILABILITY OF DVD BY SEARCHING SPECIFIC GENRE

void AddDVD() 
{
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
