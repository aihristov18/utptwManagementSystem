#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Login.h"
using namespace std;

bool validateUsernameAndPassword(nanodbc::connection conn, string username, string password)
{
    nanodbc::statement validateUser(conn);
    nanodbc::prepare(validateUser, R"(
        SELECT Username, Password
        FROM Users
        WHERE Username=? AND Password=?
    )");

    validateUser.bind(0, username.c_str());
    validateUser.bind(1, password.c_str());

    auto result = nanodbc::execute(validateUser);
    if (result.next())
    {
        return true;
    }
    return false;
}

int retrieveUserIdByPassword(nanodbc::connection conn, string password)
{
    nanodbc::statement getPassword(conn);
    nanodbc::prepare(getPassword, "SELECT Id FROM Users WHERE Password=?");
    getPassword.bind(0, password.c_str());

    auto result = nanodbc::execute(getPassword);
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