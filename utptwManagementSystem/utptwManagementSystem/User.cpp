#include "User.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;

int User::getId()
{
	return id;
}

string User::getUsername()
{
	return username;
}

bool User::getAdminStatus()
{
	return isAdmin;
}

void User::retrieveCurrentUserData()
{
	string query = "SELECT Username, FirstName, LastName, isAdmin, IdOfCreator, IdOfLastUserUpdate, DateOfCreation, DateOfLastChange FROM Users WHERE Id='" + to_string(id) + "'";
	auto result = nanodbc::execute(conn, NANODBC_TEXT(query));

	result.next();
	
	username = result.get<string>(0);
	firstName = result.get<string>(1);
	lastName = result.get<string>(2);
	idOfCreator = result.get<int>(4);
	idOfLastUserUpdate = result.get<int>(5);
	dateOfCreation = result.get<string>(6);
	dateOfLastChange = result.get<string>(7);
	
	if (result.get<int>(3) == 1) { isAdmin = true; }
	else { isAdmin = false; }
}

void User::displayUserData()
{
	cout << "-----------------------------" << endl;
	cout << endl;
	cout << "User Id: " << id << endl;
	cout << "Username: " << username << endl;
	cout << "Full name: " << firstName + " " + lastName << endl;
	cout << "Admin Status: " << isAdmin << endl;
	cout << "Date of creation: " << dateOfCreation << endl;
	cout << "Id of creator: " << idOfCreator << endl;
	cout << "Date of last update: " << dateOfLastChange << endl;
	cout << "Id of last update from user: " << idOfLastUserUpdate << endl;
	cout << endl;
	cout << "-----------------------------";
	cout << endl;
	cout << endl;
}

//To-do
void User::retrieveAllUsers()
{
	string query = "SELECT Id FROM Users";
	auto result = nanodbc::execute(conn, query);

}