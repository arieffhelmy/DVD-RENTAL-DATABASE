#include "Header.hpp"

void returnDVD() 
{
    // Name:
    // Matrix Number: 
    // Function: 

    DVD dvd;

    string findtitle;
    string line;
    stringstream updatedContent;

    // Open the file for reading and writing (in text mode)
    fstream file("DVD_Rental_Database.csv", ios::in | ios::out);

    if (!file.is_open()) 
    {
        cout << "ERROR: Unable to open the file." << '\n';
        return; 
    }

    bool foundtitle = false;

    // Prompt user to enter the movie title
    cout << "What is the name of the movie: ";
    getline(cin, findtitle);

    // Read the entire file content and process it line by line
    while (getline(file, line)) 
    {
        stringstream ss(line);  // Using stringstream to process each line

        // Read the title, genre, year, and stock from the line
        getline(ss, dvd.title, ',');
        getline(ss, dvd.genre, ',');
        getline(ss, dvd.year, ',');
        ss >> dvd.nostock;

        // Update stock if the title matches
        if (findtitle == dvd.title) 
        {
            foundtitle = true;
            dvd.nostock++;  // Increment the stock for the movie
        }

        // Write the modified line to the new content
        updatedContent << dvd.title << ',' << dvd.genre << ',' << dvd.year << ',' << dvd.nostock << '\n';
    }

    file.close(); // Close the file after reading

    // If the movie was found, inform the user
    if (!foundtitle)
    {
        cout << "Movie not found: " << findtitle << '\n';
    }
    else
    {
        cout << "The stock for '" << findtitle << "' has been updated." << '\n';
    }

    // Now, open the file for writing (to overwrite the old content with the updated one)
    file.open("DVD_Rental_Database.csv", ios::out | ios::trunc);  // Open in write mode and truncate the file

    if (!file.is_open()) 
    {
        cout << "ERROR: Unable to open the file for writing." << '\n';
        return;
    }


    file << updatedContent.str();

    file.close();

    return;
}
