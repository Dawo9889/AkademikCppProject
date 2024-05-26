#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include "User.h"
#include "Room.h"
#include "Resident.h"
using namespace std;
class Interface
{

private:
	User& user;
	Room& room;
	Resident& resident;
	
public:
	Interface(User& user, Room& room, Resident& resident);
	void welcomePage();
	int pageWhenUCanLoginOrRegisterOrExit();
	int loginPage();
	int registerPage();
	int addResident();
	
	int mainMenu();
	int administrationPanel();
	int userPanel(string &login);
	void logoutPage();
	void goodbyePage();
	int managingResidentsPage();
	int managingRoomsPage();
	int addRoomInterface();
	int deleteRoomInterface();
	int deleteResidentInterface();
	void displayResidents();
	void displayRooms();
	int updateRoomOfResident();
};