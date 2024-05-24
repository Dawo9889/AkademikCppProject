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
public:
	void welcomePage(User& user, Room& room, Resident& resident);
	int pageWhenUCanLoginOrRegisterOrExit();
	int loginPage(User& user, Room& room, Resident& resident);
	int registerPage(User& user);
	int addResident();
	int mainMenu(User& user, Room& room, Resident& resident);
	int administrationPanel(User& user, Room& room, Resident& resident);
	void logoutPage(User& user, Room& room, Resident& resident);
	int goodbyePage();
	void managingResidentsPage();
	int managingRoomsPage(User& user, Room& room, Resident& resident);
	int addRoomInterface(User& user, Room& room, Resident& resident);
};