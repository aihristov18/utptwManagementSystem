#pragma once
#include <string>

class User
{
public:
	User(int _id, std::string _username, std::string _password, std::string _firstName, std::string _lastName, bool _isAdmin)
	{
		id = _id;
		username = _username;
		password = _password;
		firstName = _firstName;
		lastName = _lastName;
		isAdmin = _isAdmin;
	}

private:
	int id;
	std::string username, password, firstName, lastName;
	bool isAdmin;
};

