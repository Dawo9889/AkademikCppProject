#pragma once
#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
using namespace std;
class User // Klasa obslugujaca zapytania do tebeli user
{
private:
	string tableName{};
public:
	int createTableUser();
	User(string& name);
};

