#pragma once
#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <random>

using namespace std;
class User // Klasa obslugujaca zapytania do tebeli user
{
private:
	string tableName{};
	string generateSalt(size_t length);
	string generateHash(const string& password, const string& salt);
	
	
public:
	int createTableUser();
	User(string& name);
	int isUserInDatabase(string& username);
	int addUser(string& username, string& email, string& password);
	string retrieveSaltFromUser(string& username);
	struct UserCredentials {
		std::string username;
		std::string password_hash;
		std::string password_salt;
	};
	UserCredentials getUserCredentials(string& username);
	bool validateCredentials(string& username, string& password);
	
};

