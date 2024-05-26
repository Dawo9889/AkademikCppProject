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
	bool isResidentInDatabase(const string& identifier, bool searchByPeselEmail); //identifier can be pesel or email, it depends on switch searchByEmail
	bool isAnyResidentInRoom(string& roomNumber);
	void displayAllResidents();
	string returnRoomNumber(string& identifier, bool searchByPeselEmail);
	int changeRoomOfResitent(string& pesel, string& room_number);
};

