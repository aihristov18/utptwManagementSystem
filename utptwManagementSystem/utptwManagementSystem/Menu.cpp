#include <iostream>
#include <nanodbc.h>
#include <Windows.h>
#include "Login.h"
#include "User.h"
using namespace std;

bool runtime()
{
    // Make connection to SQL database
    auto const connstr = NANODBC_TEXT("Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=utptwManagementSystem;Trusted_Connection=yes;");
    nanodbc::connection conn(connstr);
    int id;

    if (!login(conn, id))
    {
        return false;
    }
    Sleep(500);
    system("cls");

    User current(conn, id);
    current.retrieveUserData();

    cout << "Welcome back, " << current.getUsername() << endl;
    cout << endl;
}