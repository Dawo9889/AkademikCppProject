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
};
