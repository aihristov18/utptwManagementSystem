#include "User.h"
#include <Windows.h>
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

bool User::isAdministrator()
{
	return isAdmin;
}

void User::retrieveUserById(int _id)
{
	string query = "SELECT Username, FirstName, LastName, isAdmin, IdOfCreator, IdOfLastUserUpdate, DateOfCreation, DateOfLastChange FROM Users WHERE Id='" + to_string(_id) + "'";

	auto result = nanodbc::execute(conn, NANODBC_TEXT(query));

	result.next();
	
	id = _id;
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

void User::createUser(string _username, string _password, string _firstName, string _lastName)
{
	nanodbc::statement createUser(conn);
	nanodbc::prepare(createUser, "INSERT INTO Users (Username, Password, FirstName, LastName, IdOfCreator, DateOfLastChange, IdOfLastUserUpdate) VALUES (?, ?, ?, ?, ?, GETDATE(), ?)");

	createUser.bind(0, _username.c_str());
	createUser.bind(1, _password.c_str());
	createUser.bind(2, _firstName.c_str());
	createUser.bind(3, _lastName.c_str());
	createUser.bind(4, &id);
	createUser.bind(5, &id);

	nanodbc::execute(createUser);
}

void deleteUserById(int _id)
{

}

void User::displayUserData()
{
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
}

void User::displayAllUsers()
{
	string query = "SELECT Id FROM Users";
	auto result = nanodbc::execute(conn, NANODBC_TEXT(query));
	while (result.next())
	{
		User temp(conn);
		temp.retrieveUserById(result.get<int>(0));
		temp.displayUserData();
	}
}