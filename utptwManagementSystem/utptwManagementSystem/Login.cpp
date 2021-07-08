#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Login.h"
using namespace std;

bool validateUsernameAndPassword(nanodbc::connection conn, string username, string password)
{
    auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT Username, Password FROM Users"));
    string _username, _password;

    while (result.next())
    {
        _username = result.get<string>(0);
        _password = result.get<string>(1);

        if (_username == username and _password == password) { return true; }
    }

    return false;
}

int retrieveUserIdByPassword(nanodbc::connection conn, string password)
{
    string query = "SELECT Id FROM Users WHERE Password='" + password + "'";
    auto result = nanodbc::execute(conn, NANODBC_TEXT(query));
    result.next();
    return result.get<int>(0);
}

void passwordInput(string& password)
{
    char ch;
    do
    {
        ch = _getch();
        if (ch != '\r' and ch != char(8)) { _putch('*'); }
        if (ch == char(8))
        {
            cout << char(8) << " " << char(8);
            password.pop_back();
        }
        else
        {
            password.push_back(ch);
        }
    } while (ch != '\r');
    password.pop_back();
}

bool login(nanodbc::connection conn, int& id)
{
    bool flag = true;
    while (flag)
    {
        string username;
        string password;

        cout << "Login: " << endl;
        cout << endl;
        cout << "Username: "; cin >> username;
        cout << "Password: "; passwordInput(password);

        cout << endl;
        cout << endl;

        if (validateUsernameAndPassword(conn, username, password))
        {
            cout << "Login successful!";
            id = retrieveUserIdByPassword(conn, password);
            flag = false;
        }
        else
        {
            cout << "Login failed!";
            Sleep(600);
            system("cls");
        }
    }
    return true;
}