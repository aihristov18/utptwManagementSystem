#include <iostream>
#include <nanodbc.h>
#include "Login.h"
using namespace std;

bool runtime()
{
    // Make connection to SQL database
    auto const connstr = NANODBC_TEXT("Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=utptwManagementSystem;Trusted_Connection=yes;");
    nanodbc::connection conn(connstr);

    if (!login(conn))
    {
        return false;
    }


}