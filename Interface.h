#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
class Interface
{
public:
	void welcomePage();
	int pageWhenUCanLoginOrRegisterOrExit();
	int loginPage();
	int registerPage();
};