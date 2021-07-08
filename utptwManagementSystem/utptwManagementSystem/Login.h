#pragma once
#include <nanodbc.h>
#include <string>

bool validateUsernameAndPassword(nanodbc::connection conn, std::string username, std::string password);
int retrieveUserIdByPassword(nanodbc::connection conn, std::string password);
void passwordInput(std::string& password);
bool login(nanodbc::connection conn, int& id);