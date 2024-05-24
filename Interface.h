#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "User.h"
using namespace std;
class Interface
{
public:
	void welcomePage(User& user);
	int pageWhenUCanLoginOrRegisterOrExit();
	int loginPage();
	int registerPage(User& user);
	int addRoomToStudentHouse();
	int addResident();
	int mainMenu(User& user);
	int administrationPanel();
	void logoutPage();
	int goodbyePage();
	void managingResidentsPage();
	void managingRoomsPage();
};