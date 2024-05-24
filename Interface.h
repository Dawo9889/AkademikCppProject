#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "User.h"
#include "Room.h"
using namespace std;
class Interface
{
public:
	void welcomePage(User& user, Room& room);
	int pageWhenUCanLoginOrRegisterOrExit();
	int loginPage(Room& room);
	int registerPage(User& user);
	int addResident();
	int mainMenu(User& user, Room& room);
	int administrationPanel(Room& room);
	void logoutPage(Room& room);
	int goodbyePage();
	void managingResidentsPage();
	int managingRoomsPage(Room& room);
	int addRoomInterface(Room& room);
};