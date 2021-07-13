#pragma once
#include "User.h"
#include <string>
#include <vector>
#include <nanodbc.h>

class Team
{
public:
	Team(nanodbc::connection conn)
	{
		this->conn = conn;
	}

	void retrieveTeamById(int id);
	void retrieveAssignedUsers();
	void createTeam(std::string title, User current);
	void assignUsersToTeam(std::vector<int> userIds, int id);
	void deleteTeamById(int id);
	void editTeamById(int id, std::string title);
	void displayTeamData();
	void displayTeamById(int id);
	void displayAllTeams();
private:
	int id, creatorId, updatorId;
	std::string title, dateOfCreation, dateOfLastUpdate;
	std::vector<int> assignedUsers;
	nanodbc::connection conn;
};