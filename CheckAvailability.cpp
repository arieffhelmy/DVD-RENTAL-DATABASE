#include "Header.hpp"

//NAME: MUHAMMAD ARIEFF BIN HELMY SHAM
//MATRIX NUMBER: 23303466
//FUNCTION: TO CHECK THE AVAILABILITY OF DVD BY SEARCHING SPECIFIC GENRE

void CheckAvailability() 
{   
    ifstream ip("DVD_Rental_Database.csv");

    if (!ip.is_open()) 
    {
        cout << "ERROR: Unable to open the file." << '\n';
        return; 
    }

    string title, genre, year, nostock, findgenre, findtitle;

    cout << "What is the name of the movie: ";
    getline(cin, findtitle);

    bool foundtitle = false;

    while(getline(ip, title, ','))
    {
        getline(ip, genre, ',');
        getline(ip, year, ',');
        getline(ip, nostock, '\n');

        if (findtitle == title) 
        {
            foundtitle = true;
            cout << "Name: " << title << '\n';
            cout << "Genre: " << genre << '\n';
            cout << "Released Year: " << year << '\n';
            cout << "No of Stocks: " << nostock << '\n';
            cout << "-------------------" << '\n';
        }
    
        if (!foundtitle) 
        {
            cout << "No movies found for the title: " << findtitle << '\n';
            cout << "You can try by find specidic genre. \n\n";

            cout << "What is the genre of the movie (Action, Romance, Horror, Adventure, Fantasy): ";
            cin >> findgenre;

            bool foundgenre = false;

                while (getline(ip, title, ',')) 
                {
                    getline(ip, genre, ',');
                    getline(ip, year, ',');
                    getline(ip, nostock, '\n');

                    if (findgenre == genre) 
                    {
                        foundgenre = true;
                        cout << "Name: " << title << '\n';
                        cout << "Genre: " << genre << '\n';
                        cout << "Released Year: " << year << '\n';
                        cout << "No of Stocks: " << nostock << '\n';
                        cout << "-------------------" << '\n';
                    }
                }

                if (!foundgenre) 
                {
                    cout << "No movies found for the genre: " << findgenre << '\n';
                }
        }
    }
    
    ip.close();
}