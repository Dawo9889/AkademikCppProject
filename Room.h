#pragma once

#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
using namespace std;
class Room // klasa obslugujaca zapytania do tabeli room
{
private:
	string tableName{};
public:
	int createTableRoom();
	Room(string& name);
	int addRoom(string& roomNumber, int& numberOfBeds, bool& is_available);
	int isRoomInDatabase(string& roomNumber);
	void displayAllRooms();
	int deleteRoom(string& roomNumber);
	bool isRoomAvailable(string& roomNumber);
	bool updateRoomAvailability(string& roomNumber);
};	

