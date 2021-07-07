#pragma once
#include <nanodbc.h>
#include <string>

bool validateUsernameAndPassword(nanodbc::connection conn, std::string username, std::string password);
void getPassword(std::string& password);
bool login(nanodbc::connection conn);