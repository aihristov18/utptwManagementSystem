#include <iostream>
#include "UserPanel.h"
#include "Login.h"
#include <Windows.h>
using namespace std;

void createUserMenu(User& current)
{
	bool flag = true;
	while (flag)
	{
		string _username, _password, _firstName, _lastName;

		cout << endl;
		cout << "Enter username: "; cin >> _username;
		cout << "Enter password: "; passwordInput(_password);
		cout << endl;
		cout << "Enter first name: "; cin >> _firstName;
		cout << "Enter last name: "; cin >> _lastName;

		system("cls");

		cout << "Is this the user you want to create?" << endl
			<< endl
			<< "Username: " << _username << endl
			<< "Password: " << _password << endl
			<< "First name: " << _firstName << endl
			<< "Last name: " << _lastName << endl;

		char ch;
		cout << endl;
		cout << "Enter Y/N to proceed: "; cin >> ch;

		if (ch == 'Y')
		{
			cout << endl;
			cout << "Pushing to database .. ";
			
			current.createUser(_username, _password, _firstName, _lastName);

			Sleep(1000);
			system("cls");
			flag = false;
		}
		else if (ch == 'N')
		{
			cout << endl;
			cout << "Returning to User management menu ..";
			Sleep(1000);
			system("cls");
			flag = false;
		}
	}
}

void userManagementMenu(User& current)
{
	bool flag = true;
	while (flag)
	{
		cout << "User management menu: " << endl
			<< endl
			<< "1. View all users" << endl
			<< "2. View current user" << endl
			<< "3. Find user by id" << endl
			<< "4. Create user" << endl
			<< "5. Edit user" << endl
			<< "6. Delete user by Id" << endl
			<< endl
			<< "Enter 0 to exit." << endl
			<< endl;
		int choice;
		cout << "Enter your choice: "; cin >> choice;

		switch (choice)
		{
		case 1:
			system("cls");
			cout << "All users data:" << endl;
			current.displayAllUsers();
			break;
		case 2:
			system("cls");
			cout << "Current user data:" << endl;
			current.displayUserData();
			break;
		case 3:
			break;
		case 4:
			system("cls");
			cout << "Creating user: " << endl;
			createUserMenu(current);
			break;
		case 5:
			break;
		case 6:
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
}
