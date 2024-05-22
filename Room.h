#pragma once
#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
using namespace std;
class Room // klasa obslugujaca zapytania do tabeli pokoj
{
private:
	string tableName{};
public:
	int createTableRoom();
	Room(string& name);
};

