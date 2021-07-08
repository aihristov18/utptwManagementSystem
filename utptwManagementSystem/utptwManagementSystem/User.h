#pragma once
#include <string>
#include <nanodbc.h>

class User
{
public:
	User(nanodbc::connection conn)
	{
		this->conn = conn;
	}

	int getId();
	std::string getUsername();
	bool isAdministrator();
	void retrieveUserById(int _id);
	void createUser(std::string _username, std::string _password, std::string _firstName, std::string _lastName);
	void deleteUserById(int _id);
	void displayUserData();
	void displayAllUsers();
private:
	int id, idOfCreator, idOfLastUserUpdate;
	std::string username, firstName, lastName, dateOfCreation, dateOfLastChange;
	bool isAdmin;
	nanodbc::connection conn;
};