#include "Team.h"
#include "User.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;

void Team::retrieveTeamById(int id)
{
	nanodbc::statement retrieveTeam(conn);
	nanodbc::prepare(retrieveTeam, R"(
		SELECT Title, DateOfCreation, CreatorId, DateOfLastChange, IdOfLastUserUpdate
		FROM Teams
		WHERE Id=? AND IsDeleted!=1
	)");

	retrieveTeam.bind(0, &id);
	auto result = nanodbc::execute(retrieveTeam);

	result.next();
	
	this->id = id;
	title = result.get<string>(0);
	dateOfCreation = result.get<string>(1);
	creatorId = result.get<int>(2);
	dateOfLastUpdate = result.get<string>(3);
	updatorId = result.get<int>(4);
}

void Team::retrieveAssignedUsers()
{
	nanodbc::statement retrieveAssigned(conn);
	nanodbc::prepare(retrieveAssigned, R"(
		SELECT UserId
		FROM UsersTeams
		WHERE TeamId=?
	)");

	retrieveAssigned.bind(0, &id);

	auto result = nanodbc::execute(retrieveAssigned);

	while (result.next())
	{
		int userId = result.get<int>(0);
		assignedUsers.push_back(userId);
	}
}

void Team::createTeam(string title, User current)
{
	nanodbc::statement createTeam(conn);
	nanodbc::prepare(createTeam, R"(
		INSERT INTO Teams
		(Title, DateOfCreation, CreatorId, DateOfLastChange, IdOfLastUserUpdate)
		VALUES (?, GETDATE(), ?, GETDATE(), ?)
	)");

	int currentUserId = current.getId();

	createTeam.bind(0, title.c_str());
	createTeam.bind(1, &currentUserId);
	createTeam.bind(2, &currentUserId);

	nanodbc::execute(createTeam);
}

bool Team::validateUserIds(vector<int> userIds, int id)
{
	nanodbc::statement validateUserIds(conn);
	nanodbc::prepare(validateUserIds, R"(
		SELECT UserId
		FROM UsersTeams
		WHERE TeamId=?
	)");

	validateUserIds.bind(0, &id);
	
	auto result = nanodbc::execute(validateUserIds);

	while (result.next())
	{
		for (size_t i = 0; i < userIds.size() - 1; i++)
		{
			if (userIds[i] == result.get<int>(0))
			{
				return false;
			}
		}
	}

	return true;
}

bool Team::assignUsersToTeam(vector<int> userIds, int id)
{
	if (!validateUserIds(userIds, id))
	{
		return false;
	}

	for (size_t i = 0; i < userIds.size() - 1; i++)
	{
		nanodbc::statement assignUser(conn);
		nanodbc::prepare(assignUser, R"(
			INSERT INTO UsersTeams
			(UserId, TeamId)
			VALUES (?, ?)
		)");

		assignUser.bind(0, &userIds[i]);
		assignUser.bind(1, &id);

		nanodbc::execute(assignUser);
	}

	return true;
}

void Team::deleteTeamById(int id)
{
	nanodbc::statement deleteTeam(conn);
	nanodbc::prepare(deleteTeam, R"(
		UPDATE Teams
		SET IsDeleted=1
		WHERE Id=?
	)");

	deleteTeam.bind(0, &id);
	nanodbc::execute(deleteTeam);
}

void Team::editTeamById(int id, string title)
{
	nanodbc::statement editTeam(conn);
	nanodbc::prepare(editTeam, R"(
		UPDATE Teams
		SET Title=?
		WHERE Id=?
	)");

	editTeam.bind(0, title.c_str());
	editTeam.bind(1, &id);

	nanodbc::execute(editTeam);
}

void Team::displayTeamData()
{
	cout << endl;
	cout << "Team Id: " << id << endl;
	cout << "Title: " << title << endl;
	cout << "Date of creation: " << dateOfCreation << endl;
	cout << "Id of creator: " << creatorId << endl;

	retrieveAssignedUsers();
	cout << "Assigned users ids: ";
	for (size_t i = 0; i < assignedUsers.size(); i++)
	{
		cout << assignedUsers[i] << " ";
	}
	cout << endl;

	cout << "Date of last update: " << dateOfLastUpdate << endl;
	cout << "Id of last update from user: " << updatorId << endl;
	cout << endl;
	cout << "-----------------------------";
	cout << endl;
}

void Team::displayTeamById(int id)
{
	Team temp(conn);
	temp.retrieveTeamById(id);
	temp.displayTeamData();
}

void Team::displayAllTeams()
{
	nanodbc::statement displayTeams(conn);
	nanodbc::prepare(displayTeams, R"(
		SELECT Id
		FROM Teams
		Where IsDeleted!=1
	)");

	auto result = nanodbc::execute(displayTeams);

	while (result.next())
	{
		displayTeamById(result.get<int>(0));
	}
}