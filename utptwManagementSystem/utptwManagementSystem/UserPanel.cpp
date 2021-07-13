#include "UserPanel.h"
#include "Login.h"
#include <iostream>
#include <exception>
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

		if (ch == 'Y' or ch == 'y')
		{
			cout << endl;
			cout << "Pushing to database .. ";
			
			current.createUser(_username, _password, _firstName, _lastName);

			Sleep(1000);
			system("cls");
			flag = false;
		}
		else if (ch == 'N' or ch == 'n')
		{
			cout << endl;
			cout << "Returning to User management menu ..";
			Sleep(1000);
			system("cls");
			flag = false;
		}
	}
}

void deleteUserMenu(User& current)
{
	int id;
	cout << endl;
	cout << "Enter user Id to delete: "; cin >> id;
	if (id == current.getId())
	{
		cout << endl;
		cout << "You can't delete your own account!";
		Sleep(600);
	}
	else
	{
		cout << endl;
		current.deleteUserById(id);
	}
	system("cls");
}

void displayUserByIdMenu(User& current)
{
	int id;
	cout << "Enter user id: "; cin >> id;
	current.displayUserById(id);
}

void editUserMenu(User& current)
{
	bool flag = true;
	while (flag)
	{
		int id;
		cout << "Enter user id to edit: "; cin >> id;
		current.displayUserById(id);

		char choice;

		cout << endl;
		cout << "Is this the user you want to edit? (Y/N): "; cin >> choice;

		
		if (choice == 'Y' or choice == 'y')
		{
			string username, password, firstName, lastName;

			cout << endl;
			cout << "Enter new username: "; cin >> username;
			cout << "Enter new password: "; cin >> password;
			cout << "Enter new first name: "; cin >> firstName;
			cout << "Enter new last name: "; cin >> lastName;

			current.editUserById(id, username, password, firstName, lastName);
			flag = false;
		}
		else if (choice == 'N' or choice == 'n')
		{
			system("cls");
		}
	}
}

void userManagementMenu(User& current)
{
	bool flag = true;
	while(flag)
	{
		try
		{
			cout << "User management menu: " << endl
				<< endl
				<< "1. View all users" << endl
				<< "2. View current user" << endl
				<< "3. Find user by id" << endl
				<< "4. Create user" << endl
				<< "5. Edit user" << endl
				<< "6. Delete user by id" << endl
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
				system("cls");
				displayUserByIdMenu(current);
				break;
			case 4:
				system("cls");
				cout << "Creating user: " << endl;
				createUserMenu(current);
				break;
			case 5:
				system("cls");
				cout << "Edit user menu:" << endl;
				cout << endl;
				editUserMenu(current);
				system("cls");
				break;
			case 6:
				system("cls");
				cout << "Delete user menu:" << endl;
				deleteUserMenu(current);
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
		catch (exception& e)
		{
			cerr << e.what() << endl;
			cout << endl;
		}
	}
}
