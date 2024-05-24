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
	int loginPage(User& user, Room& room);
	int registerPage(User& user, Room& room);
	int addResident();
	int mainMenu(User& user, Room& room);
	int administrationPanel(User& user, Room& room);
	void logoutPage(User& user, Room& room);
	int goodbyePage();
	void managingResidentsPage();
	int managingRoomsPage(User& user, Room& room);
	int addRoomInterface(User& user, Room& room);
};