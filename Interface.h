#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;
class Interface
{
public:
	void welcomePage();
	int pageWhenUCanLoginOrRegisterOrExit();
	int loginPage();
	int registerPage();
	int addRoomToStudentHouse();
	int addResident();
	int mainMenu();
	int administrationPanel();
	void logoutPage();
	int goodbyePage();
	void managingResidentsPage();
	void managingRoomsPage();
};