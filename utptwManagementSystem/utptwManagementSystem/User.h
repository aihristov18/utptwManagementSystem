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
	void retrieveUserById(int id);
	void createUser(std::string _username, std::string _password, std::string _firstName, std::string _lastName);
	void deleteUserById(int id);
	void editUserById(int id, std::string username, std::string password, std::string firstName, std::string lastName);
	void displayUserData();
	void displayUserById(int id);
	void displayAllUsers();
private:
	int id, idOfCreator, idOfLastUserUpdate;
	std::string username, firstName, lastName, dateOfCreation, dateOfLastChange;
	bool isAdmin;
	nanodbc::connection conn;
};