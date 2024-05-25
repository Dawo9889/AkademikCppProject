#pragma once

#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
using namespace std;
class Resident // Klasa obslugujaca zapytania do SQL dla tabeli mieszkancy
{
private:
	string tableName{};
public:
	int createTableResident();
	Resident(string& name);
	int addResident(string& PESEL, string& firstName, string& lastName, string& email, int roomNumber);
	bool isResidentInDatabase(string& PESEL);
};

