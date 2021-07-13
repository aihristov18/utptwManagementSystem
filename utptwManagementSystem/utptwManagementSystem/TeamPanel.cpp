#include "TeamPanel.h"
#include "Team.h"
#include "Login.h"
#include <iostream>
#include <vector>
#include <exception>
#include <conio.h>
#include <Windows.h>
using namespace std;

void displayAllTeamsMenu(User current)
{
	Team temp(current.getConnection());
	temp.displayAllTeams();
}

void createTeamMenu(User current)
{
	bool flag = true;
	while (flag)
	{
		string title;

		cout << endl;
		cout << "Enter team title: "; cin >> title;

		char ch;
		cout << endl;
		cout << "Enter Y/N to proceed: "; cin >> ch;

		if (ch == 'Y' or ch == 'y')
		{
			Team temp(current.getConnection());

			cout << endl;
			cout << "Pushing to database .. ";

			temp.createTeam(title, current);

			Sleep(1000);
			system("cls");

			flag = false;
		}
		else if (ch == 'N' or ch == 'n')
		{
			cout << endl;
			cout << "Returning to Team management menu ..";
			Sleep(1000);
			system("cls");

			flag = false;
		}
	}
}

void assignUsersMenu(User current)
{
	bool flag = true;
	while (flag)
	{
		vector<int> userIds;
		int teamId;

		cout << endl;
		cout << "Teams you can assign users to: " << endl;

		displayAllTeamsMenu(current);

		cout << endl;
		cout << "Enter team id: "; cin >> teamId;

		char ch;
		cout << endl;
		cout << "Enter Y/N to proceed: "; cin >> ch;

		if (ch == 'Y' or ch == 'y')
		{
			Team temp(current.getConnection());

			system("cls");

			cout << "Available users: ";

			current.displayAllUsers();

			cout << endl;
			cout << "Enter user ids (Enter 0 to exit): ";

			bool flag1 = true;
			
			while (flag1)
			{
				int num;
				cin >> num;
				
				if (num == 0)
				{
					flag1 = false;
				}

				userIds.push_back(num);
			}

			if (!temp.assignUsersToTeam(userIds, teamId))
			{
				cout << endl;
				cout << "One of the users you entered is already assigned to this team." << endl;
			}
			else
			{
				cout << endl;
				cout << "Pushing to database .. ";
			}

			Sleep(1000);
			system("cls");

			flag = false;
		}
		else if (ch == 'N' or ch == 'n')
		{
			cout << endl;
			cout << "Returning to Team management menu ..";
			Sleep(1000);
			system("cls");

			flag = false;
		}
	}
}

void deleteTeamMenu(User current)
{
	
	Team temp(current.getConnection());
	int id;
	cout << endl;
	cout << "Enter team id to delete: "; cin >> id;
	temp.deleteTeamById(id);
	system("cls");
}

void displayTeamByIdMenu(User current)
{
	int id;
	Team temp(current.getConnection());
	cout << "Enter team id: "; cin >> id;
	temp.displayTeamById(id);
}

void editTeamMenu(User current)
{
	bool flag = true;
	while (flag)
	{
		Team temp(current.getConnection());
		int id;
		cout << "Enter team id to edit: "; cin >> id;
		temp.displayTeamById(id);

		char choice;

		cout << endl;
		cout << "Is this the team you want to edit? (Y/N): "; cin >> choice;


		if (choice == 'Y' or choice == 'y')
		{
			string title;

			cout << endl;
			cout << "Enter new title: "; cin >> title;

			cout << endl;
			temp.editTeamById(id, title);
			flag = false;
		}
		else if (choice == 'N' or choice == 'n')
		{
			system("cls");
		}
	}
}

void teamManagementMenu(User current)
{
	bool flag = true;
	while (flag) try
	{
		{
			cout << "Team management menu: " << endl
				<< endl
				<< "1. View all teams" << endl
				<< "2. Find team by id" << endl
				<< "3. Create team" << endl
				<< "4. Assign users to team" << endl
				<< "5. Edit team" << endl
				<< "6. Delete team by id" << endl
				<< endl
				<< "Enter 0 to exit." << endl
				<< endl;

			int choice;
			cout << "Enter your choice: "; cin >> choice;

			switch (choice)
			{
			case 1:
				system("cls");
				cout << "All teams data:" << endl;
				displayAllTeamsMenu(current);
				break;
			case 2:
				system("cls");
				displayTeamByIdMenu(current);
				break;
			case 3:
				system("cls");
				cout << "Creating team: " << endl;
				createTeamMenu(current);
				break;
			case 4:
				system("cls");
				cout << "Assign users:" << endl;
				assignUsersMenu(current);
				break;
			case 5:
				system("cls");
				cout << "Edit team menu:" << endl;
				cout << endl;
				editTeamMenu(current);
				break;
			case 6:
				system("cls");
				cout << "Delete team menu:" << endl;
				deleteTeamMenu(current);
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
	catch (exception& e)
	{
		cerr << e.what() << endl;
		cout << endl;
	}
}