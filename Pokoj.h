#pragma once
#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
using namespace std;
class Pokoj // klasa obslugujaca zapytania do tabeli pokoj
{
private:
	string tableName{};
public:
	int createTablePokoj();
	Pokoj(string& name);
};

