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

nanodbc::connection User::getConnection()
{
	return conn;
}

void User::retrieveUserById(int id)
{
	nanodbc::statement retrieveUser(conn);
	nanodbc::prepare(retrieveUser, R"(
		SELECT Username, FirstName, LastName, isAdmin, IdOfCreator, IdOfLastUserUpdate, DateOfCreation, DateOfLastChange 
		FROM Users 
		WHERE Id=? AND isDeleted!=1
	)");
	retrieveUser.bind(0, &id);
	auto result = nanodbc::execute(retrieveUser);

	result.next();
	
	this->id = id;

	username = result.get<string>(0);

	if (result.is_null(1)) { firstName = ""; }
	else { firstName = result.get<string>(1); }

	if (result.is_null(2)) { lastName = ""; }
	else { lastName = result.get<string>(2); }

	if (result.is_null(4)) { idOfCreator = NULL; }
	else { idOfCreator = result.get<int>(4); }

	if (result.is_null(5)) { idOfLastUserUpdate = NULL; }
	else { idOfLastUserUpdate = result.get<int>(5); }
	
	dateOfCreation = result.get<string>(6);
	dateOfLastChange = result.get<string>(7);
	
	if (result.get<int>(3) == 1) { isAdmin = true; }
	else { isAdmin = false; }
}

void User::createUser(string _username, string _password, string _firstName, string _lastName)
{
	nanodbc::statement createUser(conn);
	nanodbc::prepare(createUser, R"(
		INSERT INTO Users 
		(Username, Password, FirstName, LastName, IdOfCreator, DateOfLastChange, IdOfLastUserUpdate) 
		VALUES (?, ?, ?, ?, ?, GETDATE(), ?)
)");

	createUser.bind(0, _username.c_str());
	createUser.bind(1, _password.c_str());
	createUser.bind(2, _firstName.c_str());
	createUser.bind(3, _lastName.c_str());
	createUser.bind(4, &id);
	createUser.bind(5, &id);

	nanodbc::execute(createUser);
}

void User::deleteUserById(int id)
{
	nanodbc::statement deleteUser(conn);
	nanodbc::prepare(deleteUser, R"(
			UPDATE Users
			SET isDeleted=1
			WHERE Id=?
		)");
	deleteUser.bind(0, &id);
	nanodbc::execute(deleteUser);
}

void User::editUserById(int id, string username, string password, string firstName, string lastName)
{
	nanodbc::statement editUser(conn);
	nanodbc::prepare(editUser, R"(
		UPDATE Users
		SET Username=?, Password=?, FirstName=?, LastName=?, IdOfLastUserUpdate=?, DateOfLastChange=GETDATE()
		WHERE Id=?
)");

	editUser.bind(0, username.c_str());
	editUser.bind(1, password.c_str());
	editUser.bind(2, firstName.c_str());
	editUser.bind(3, lastName.c_str());
	editUser.bind(4, &this->id);
	editUser.bind(5, &id);

	nanodbc::execute(editUser);
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

void User::displayUserById(int id)
{
	User temp(conn);
	temp.retrieveUserById(id);
	temp.displayUserData();
}

void User::displayAllUsers()
{
	string query = "SELECT Id FROM Users WHERE isDeleted!=1";
	auto result = nanodbc::execute(conn, NANODBC_TEXT(query));
	while (result.next())
	{
		displayUserById(result.get<int>(0));
	}
}