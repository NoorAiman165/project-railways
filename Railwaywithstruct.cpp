#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <windows.h>
using namespace std;

// Global constants
const int num = 10;     // max number of trains
const int passengers = 100; // max number of passengers

// Struct definition for Train
struct Train {
    int ID;
    string name;
    string terminal;
    string timing;
    int total_seats;
    int ticket_price;
};

// Function to add a train
int addtrain(Train trains[], int num) {
    char choice;
    do {
        bool added = false;
        for (int i = 0; i < num; i++) {
            if (trains[i].ID == 0) { // Check for an empty slot
                cout << "Enter train ID: ";
                cin >> trains[i].ID;
                cin.ignore();

                cout << "Enter train name: ";
                getline(cin, trains[i].name);

                cout << "Enter Terminals of the train: ";
                getline(cin, trains[i].terminal);

                cout << "Enter the timings of the train: ";
                getline(cin, trains[i].timing);

                cout << "Enter the Total seats in the train: ";
                cin >> trains[i].total_seats;

                cout << "Enter the Ticket price: ";
                cin >> trains[i].ticket_price;

                added = true;
                cout << "Data for the train is added successfully\n";
                break;
            }
        }

        if (!added) {
            cout << "No available space to add a new train.\n";
            break;
        }

        cout << "Do you want to add another train? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice == 'Y');
    return 0;
}

// Function to delete a train
void Deletetrain(Train trains[], int num) {
    bool find = false;
    int id;
    cout << setw(30) << "*********Deleting Train***********";
    cout << "\n\nEnter the Train ID you want to delete: ";
    cin >> id;
    for (int i = 0; i < num; i++) {
        if (trains[i].ID == id) {
            trains[i] = {0, "", "", "", 0, 0}; // Reset the struct
            find = true;
            break;
        }
    }
    if (!find) {
        cout << "Invalid Train ID!!!!!\n";
    }
}

// Function to edit train data
void edittrain(Train trains[], int num) {
    bool find = false;
    int id;
    cout << setw(30) << "*********Editing Train***********\n\n";
    cout << "Enter the Train ID you want to edit: ";
    cin >> id;
    for (int i = 0; i < num; i++) {
        if (trains[i].ID == id) {
            cout << "Enter edited train ID: ";
            cin >> trains[i].ID;
            cout << "Enter edited train name: ";
            cin.ignore();
            getline(cin, trains[i].name);
            cout << "Enter edited Terminals of the train: ";
            getline(cin, trains[i].terminal);
            cout << "Enter the edited timings of the train: ";
            getline(cin, trains[i].timing);
            cout << "Enter the edited Total seats in the train: ";
            cin >> trains[i].total_seats;
            cout << "Enter the edited Ticket price: ";
            cin >> trains[i].ticket_price;

            cout << "Data for edited train is added successfully\n";
            find = true;
            break;
        }
    }
    if (!find) {
        cout << "Invalid Train ID!!!!!\n";
    }
}

// Function to display available terminals
void showterminal(const Train trains[], int num) {
    cout << "******Available Terminals and Trains Name & Price of tickets******\n";
    for (int i = 0; i < num; i++) {
        if (trains[i].ID != 0) {
            cout << i << setw(30) << "." << setw(30) << trains[i].ID
                 << setw(30) << trains[i].terminal << setw(30) << trains[i].ticket_price << endl;
        }
    }
}

// Function to book tickets
void bookticket(Train trains[], int& reserved_seats, int num) {
    int j;
    bool find = false;
    cout << "Enter ID to book ticket: ";
    cin >> j;
    for (int i = 0; i < num; i++) {
        if (trains[i].ID == j) {
            find = true;
            if (trains[i].total_seats > 0) {
                string passenger_name;
                cin.ignore();
                cout << "Enter the name of the passenger: ";
                getline(cin, passenger_name);

                ofstream file("passengerrecords.txt", ios::app);
                if (file.is_open()) {
                    file << passenger_name << " " << j << "\n";
                    file.close();
                    reserved_seats++;
                    trains[i].total_seats--;
                    cout << "Ticket is booked successfully!!!!\n";
                } else {
                    cout << "File is not opened\n";
                }
                break;
            } else {
                cout << "No seats are available in this train!!!\n";
                break;
            }
        }
    }
    if (!find) {
        cout << "Invalid ID\n";
    }
}

// Function to cancel tickets
void cancelticket(Train trains[], int& reserved_seats, int num) {
    string passenger_name;
    int j;
    bool booking_find = false;
    cout << "Enter name to cancel ticket: ";
    cin.ignore();
    getline(cin, passenger_name);
    cout << "Enter train ID: ";
    cin >> j;

    ifstream file("passenger.txt");
    ofstream temp("temp.txt");
    if (temp.is_open() && file.is_open()) {
        string name;
        int id;
        while (file >> name >> id) {
            if (name == passenger_name && id == j) {
                booking_find = true;
                for (int i = 0; i < num; i++) {
                    if (trains[i].ID == j) {
                        trains[i].total_seats++;
                        reserved_seats--;
                        cout << "Ticket Cancelled Successfully\n";
                        break;
                    }
                }
            } else {
                temp << name << " " << id << "\n";
            }
        }
        file.close();
        temp.close();
        remove("passenger.txt");
        rename("temp.txt", "passenger.txt");
    } else {
        cout << "Error\n";
    }
    if (!booking_find) {
        cout << "You have not booked a ticket\n";
    }
}

// Function to show train information
void showtraininfo(const Train trains[], int num) {
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(20) << "Terminal"
         << setw(20) << "Timing" << setw(10) << "Seats" << setw(10) << "Price" << endl;
    for (int i = 0; i < num; i++) {
        if (trains[i].ID != 0) {
            cout << left << setw(10) << trains[i].ID << setw(20) << trains[i].name
                 << setw(20) << trains[i].terminal << setw(20) << trains[i].timing
                 << setw(10) << trains[i].total_seats << setw(10) << trains[i].ticket_price << endl;
        }
    }
}

// Function to save train information
void loadtraininfo(Train trains[], int num) {
    ifstream file("trainrecords.txt");
    if (!file.is_open()) {
        cout << "Error opening file.\n";
        return;
    }
    int i = 0;
    while (i < num && file >> trains[i].ID >> ws &&
           getline(file, trains[i].name, ' ') &&
           getline(file, trains[i].terminal, ' ') &&
           getline(file, trains[i].timing, ' ') &&
           file >> trains[i].total_seats >> trains[i].ticket_price) {
        i++;
    }
    file.close();
}

// Main Function
int main() {

    const int num=10; // max number of trains
const int passengers=100; // max number of passengers
int IDtrain[num]={0};
string nametrain[num]={""};
string terminal[num]={""};
string timing[num]={""};
int total_seats[num]={0};
string passengers_data[num]={""};
int passengercount=0;
int ticket_price[num]={0};
int reserved_seats=0;
string username;
string pwd;
string uname;
string pasw;
int input=0;
int selectiontype=-10; 
Train trains[num] = {};
//display welcome 
do
{
    HANDLE h= 
 GetStdHandle(STD_OUTPUT_HANDLE);

SetConsoleTextAttribute(h,13);
cout << "    ____        __       ____        _ __                          "
<< endl;
cout << "   / __ /____ _/ /__    / __ |____ _(_) /      ______ ___  _______ " << endl;
cout << "  / /_/ / __ `/ //_/   / /_/ / __ `/ / / | /| / / __ `/ / / / ___/ " << endl;
cout << " / ____/ /_/ / ,<     / _, _/ /_/ / / /| |/ |/ / /_/ / /_/ (__  ) "  << endl; 
cout << "/_/    |__,_/_/|_|   /_/ |_||__,_/_/_/ |__/|__/|__,_/|__, /____/  "  << endl; 
cout << "                                                     /____/       "  << endl;
// Main Menu
SetConsoleTextAttribute(h,11);
    cout << "\t\t\t*******<Choose one option from the following>*******" << endl;
    cout << endl;
    cout << endl;



    cout << left << setw(10) << "\t"
    << setw(25) << "1.Administrator"
    << setw(25) << "2.passenger"
    << setw(25) << "0.Exit";
     cout << endl;
     cout << "Enter your option:";
    cin >> input;
    // Main menu optins
    switch(input)
    {
        case 1:
        // Administrator login
        {
        cout << "Enter the user name:";
        cin >> username;
        cout << endl;
        cout << "please enter the password:";
        cin >> pwd;
        // verify administrator credentials
        if((username=="Noor12")&&(pwd=="Pakistan1"))
        {
            selectiontype=1;
        }
        else
        {
            selectiontype=-1;
        }
        }
        break;
        case 2:
        //  User Login
        {
            if(passengercount>=passengers)
            {
                cout << "passenger list is full";
                cout << endl;
            }
            cout << "Type 'user' to get into the system :";
            cin >> uname;
            cout << "Enter 'pakrailways' to enter intoo the system :";
            cin >> pasw;
            // Verify passengers credentials
            if(uname=="user"&&pasw=="pakrailways")
            {
            selectiontype=2;
            }
        
        }
        break;
        case 0:
        {
            selectiontype=-10;
            cout << "Thank You for using the System! :)";
        }
        break;
        // invalid choice handling
        default:
        {
            cout << "Invalid Choice:(";
            cout << endl;
        }

    }
        // Show manager dashboard
    if(selectiontype==1)
    {
        SetConsoleTextAttribute(h,6);
        cout << left << setw(30) <<  "MANAGER DASHBOARD" << endl;
        do
        {
          // show manager options  

            cout << "\t\t\t********<Choose the option>********" << endl;
            cout << left << setw(20) << "\tOptions"
            << endl
            << left << setw(20) << "1.Add Train & its details"
            << endl
            << left<< setw(20) << "2. Delete Train & its data"
            << endl
            << left << setw(20) << "3. Edit Train & its data"
            << endl 
            << left << setw(20) << "4.Save Train information"
            << endl
            << left << setw(20) << "5.show Train information"
            << endl
            << left << setw(20) << "0.Exit"
            << endl;
            cout <<"Enter your option:";
            cin >> input;
            switch (input)
            {
            case 1:
           {
            // calling function to add a train
            addtrain(trains, num);
           }
            break;
           case 2:
          {
            // calling function to delete train
            Deletetrain(trains,  num);
          }
           break;
           case 3:
           {
            // calling function to edit train data
            edittrain( trains,  num);
           }
           break;
            case 4:
            {
                // code to save train data
             loadtraininfo(trains,  num);

            }
            break;
            case 5:
            {
                // code to show train data
                showtraininfo(trains,  num);
            }
            break;
            case 0:
            cout << "Thank You for using the system " << setw(3) << ":)" << endl;
            break;
            default:
            {
                cout << "invalid choice";
                cout << endl;
            }
            break;
            }
            cout << endl;
            }

        
        while(input!=0);
        input=-1;
    }
    // passengers main menu
    else if(selectiontype==2)
    {
SetConsoleTextAttribute(h,2);
        cout << setw(30) <<"PASSENGER DASHBOARD" << endl;
        do
        {
            // show passengers options
            cout << setw(30) << "********<Choose from following option>********" << endl;
            cout << left << setw(10) << "\toptions" << endl
            << left << setw(25) << "1.Available terminals"
            << left << setw(25) << "2.Book Tickets"
            << left << setw(25) << "3.Save data"
            << left << setw(25) << "0.Exit"

            << endl;
            cout << "Enter your choice:";
            cin >> input;
            switch(input)
            {
             // show avilable trains and its data   
            case 1:
            {
             showterminal(trains, num);
            }
                break;
            case 2:
            {
                bookticket(trains,reserved_seats,num);
            }
                break;
            case 3:
          {
            cancelticket(trains,reserved_seats,num);
          }
            break;
            case 0:
            {
            cout << "Thank You for using the system " << setw(3) << ":)" << endl;
            break;
            }
            default:
            {
                cout << "invalid";
            }
        }
        }
        while(input!=0);
        input=-10;
    }
    }
    while (input!=0);
return 0;
}
