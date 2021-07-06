#include <nanodbc.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <vector>
using namespace std;

bool validateUsernameAndPassword(nanodbc::connection conn, string username, string password)
{
    auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Username, Password FROM Users"));
    string _tempUsername, _tempPassword;

    while (result.next())
    {
        _tempUsername = result.get<string>(0);
        _tempPassword = result.get<string>(1);

        if (username == _tempUsername and password == _tempPassword)
        {
            return true;
        }
    }
    return false;
}
 
bool login(nanodbc::connection conn)
{
    bool flag = true;
    while (flag)
    {
        string username;
        string password;
        int i = 0;

        cout << "Login: " << endl;
        cout << endl;
        cout << "Username: "; cin >> username;
        cout << "Password: "; cin >> password;

        cout << endl;
        cout << endl;

        if (validateUsernameAndPassword(conn, username, password))
        {
            cout << "Login successful!";
            flag = false;
        }
        else
        {
            cout << "Login failed!";
            Sleep(500);
            system("cls");
        }
    }
    return true;
}

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

int main() try
{
    bool isRunning = true;
    if (isRunning)
    {
        isRunning = runtime();
    }
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}