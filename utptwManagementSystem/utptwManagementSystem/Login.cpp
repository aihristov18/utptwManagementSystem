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

int retrieveUserId(nanodbc::connection conn, string password)
{
    string query = "SELECT Id FROM Users WHERE Password='" + password + "'";
    auto result = nanodbc::execute(conn, NANODBC_TEXT(query));
    result.next();
    return result.get<int>(0);
}

//Rework
void passwordInput(string& password)
{
    char ch;
    do
    {
        ch = _getch();
        password.push_back(ch);
        if (ch != '\r') { _putch('*'); }
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
        int i = 0;

        cout << "Login: " << endl;
        cout << endl;
        cout << "Username: "; cin >> username;
        cout << "Password: "; passwordInput(password);

        cout << endl;
        cout << endl;

        if (validateUsernameAndPassword(conn, username, password))
        {
            cout << "Login successful!";
            id = retrieveUserId(conn, password);
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