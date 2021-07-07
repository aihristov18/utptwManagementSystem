#include <iostream>
#include "UserPanel.h"
#include <Windows.h>
using namespace std;

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
			<< "6. Delete user" << endl
			<< endl
			<< "Enter 0 to exit." << endl
			<< endl;
		int choice;
		cout << "Enter your choice: "; cin >> choice;

		switch (choice)
		{
		case 1:
			break;
		case 2:
			system("cls");
			cout << "Current user data:" << endl;
			current.displayUserData();
			break;
		case 3:
			break;
		case 4:
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
