#pragma once
#include <string>
#include <nanodbc.h>

class User
{
public:
	User(nanodbc::connection conn, int id)
	{
		this->conn = conn;
		this->id = id;  
	}

	int getId();
	std::string getUsername();
	bool getAdminStatus();
	void retrieveCurrentUserData();
	void displayUserData();
	void retrieveAllUsers();
private:
	int id, idOfCreator, idOfLastUserUpdate;
	std::string username, firstName, lastName, dateOfCreation, dateOfLastChange;
	bool isAdmin;
	nanodbc::connection conn;
};

