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
	int deleteResident(string& PESEL);
	bool isResidentInDatabase(string& PESEL);
	bool isAnyResidentInRoom(string& roomNumber);
	void displayAllResidents();
	string returnRoomNumber(string& PESEL);
	int changeRoomOfResitent(string& pesel, string& room_number);
};

