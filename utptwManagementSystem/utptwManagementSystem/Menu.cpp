#include <iostream>
#include <nanodbc.h>
#include <Windows.h>
#include "Login.h"
#include "User.h"
#include "UserPanel.h"
using namespace std;

bool runtime()
{
    // Make connection to SQL database
    auto const connstr = NANODBC_TEXT("Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=utptwManagementSystem;Trusted_Connection=yes;MARS_Connection=Yes;");
    nanodbc::connection conn(connstr);
    int id;

    if (!login(conn, id))
    {
        return false;
    }
    Sleep(500);
    system("cls");

    User current(conn);
    current.retrieveUserById(id);

    cout << "Welcome back, " << current.getUsername() << endl;
    cout << endl;

    bool flag = true;
    while (flag)
    {
        cout << "Menu: " << endl;
        cout << endl;

        if (current.isAdministrator())
        {
            int choice;
            cout << "1. User Management Panel" << endl;
            cout << "2. Teams Management Panel" << endl;
            cout << "3. Projects Management Panel" << endl;
            cout << endl;
            cout << "Enter 0 to exit." << endl;
            cout << endl;
            cout << "Enter your choice: "; cin >> choice;
            
            switch (choice)
            {
            case 1:
                system("cls");
                userManagementMenu(current);
                break;
            case 2:
                break;
            case 3:
                break;
            case 0:
                flag = false;
                break;
            default:
                cout << endl;
                cout << "Invalid input!";
                Sleep(500);
                system("cls");
            }
        }
        else
        {
            int choice;
            cout << "1. Projects Management Panel" << endl;
            cout << endl;
            cout << "Enter 0 to exit." << endl;
            cout << endl;
            cout << "Enter your choice: "; cin >> choice;

            switch (choice)
            {
            case 1:
                break;
            case 0:
                flag = false;
                break;
            default:
                cout << endl;
                cout << "Invalid input!";
                Sleep(500);
                system("cls");
            }
        }
        system("cls");
    }
}