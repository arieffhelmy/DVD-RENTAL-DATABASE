#include "Header.hpp"

//NAME: ANNEETA A/P CHAM LONG
//MATRIX NUMBER: 23303421
//FUNCTION: TO ADD A NEW DVD AND ADD STOCK TO AN EXISTING DVD


void AddDVDandStock()
{ 
    int choice;
    string line, title;
    vector<DVD> dvdCollection;
    DVD dvd;
    
    while (true) 
    {
        cout << "\n1. Add a new DVD\n";
        cout << "2. Add stock to an existing DVD\n";
        cout << "0. Return to main menu\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        cin.ignore(); 
        
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid! Please enter number only.\n";
        }
        else 
        {
            if (choice == 0) 
            {
                break;  //Return to the main menu
            }
            else if (choice == 1) 
            {
                DVD dvd;

                ifstream input("DATA/DVD_Rental_Database.csv");
                if (input.fail()) 
                {
                    cout << "The file cannot be opened for reading." << '\n';
                    return;
                }

                bool exists = false;

                cout << "Enter the name of the movie: ";
                getline(cin, dvd.title);

                // Check if the title already exists
                while (getline(input, line)) 
                {
                    stringstream ss(line);
                    getline(ss, title, ',');
                    
                    if (normalizeString(title) == normalizeString(dvd.title)) 
                    {
                        exists = true;
                    }
                }

                input.close();

                if (exists) 
                {
                    cout << "The movie title already exists in the database.\n";
                    break; //Return to main menu
                }
                else
                {
                    ofstream output("DATA/DVD_Rental_Database.csv", ios::app);
                    if (output.fail()) 
                    {
                        cout << "The file cannot be opened for writing." << '\n';
                        return;
                    }

                    cout << "Enter the genre of the movie: ";
                    getline(cin, dvd.genre);

                    cout << "Enter the release year of the movie: ";
                    cin >> dvd.year;

                    cout << "Enter the number of stocks available: ";
                    cin >> dvd.nostock;
                    cin.ignore();
        
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid! Please enter number only.\n";
                        return;
                    }

                    output << dvd.title << "," 
                        << dvd.genre << "," 
                        << dvd.year << "," 
                        << dvd.nostock << endl;

                    cout << "\nDVD added successfully!" << '\n';

                    output.close();
                }
            }
            else if (choice == 2) 
            {
                fstream inout;
                string header;

                inout.open("DATA/DVD_Rental_Database.csv", ios::in);
                if (inout.is_open()) 
                {
                    getline(inout, header);

                    while (getline(inout, line)) 
                    {
                        stringstream ss(line);
                        getline(ss, dvd.title, ',');
                        getline(ss, dvd.genre, ',');
                        getline(ss, dvd.year, ',');
                        ss >> dvd.nostock;
                        dvdCollection.push_back(dvd);
                    }
                    inout.close();
                } 
                else 
                {
                    cout << "The file cannot be opened." << '\n';
                    continue;
                }

                cout << "Enter the name of the movie: ";
                getline(cin, dvd.title);

                bool founddvd = false;

                // Search for the DVD by title
                for (auto& existingDVD : dvdCollection) 
                {
                    if (normalizeString(existingDVD.title) == normalizeString(dvd.title)) 
                    {
                        founddvd = true;
                        int addedStock;

                        cout << "Enter the number of stocks to add: ";
                        cin >> addedStock;
                        cin.ignore();
            
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid! Please enter number only.\n";
                            return;
                        }
                        else
                        {
                            existingDVD.nostock += addedStock;
                            break;
                        }
                    }
                }

                if (!founddvd) 
                {
                    cout << "DVD not found in the database!" << endl;
                    continue;
                }

                inout.open("DATA/DVD_Rental_Database.csv", ios::out | ios::trunc);

                if (inout.fail()) 
                {
                    cout << "The file cannot be opened." << '\n';
                    continue;
                }

                inout << header << "\n"; 
                for (const auto& existingDVD : dvdCollection) 
                {
                    if (!existingDVD.title.empty())
                    {
                    inout << existingDVD.title << ","
                        << existingDVD.genre << ","
                        << existingDVD.year << ","
                        << existingDVD.nostock << endl;
                    }
                }

                cout << "\nStock added successfully!" << '\n';
                inout.close();
            }
            else 
            {
                cout << "Invalid choice. Please select 0, 1, or 2." << endl;
            }
        }
    }
}
