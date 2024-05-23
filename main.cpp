#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include "Resident.h";
#include "Room.h";
#include "Interface.h"
using namespace std;

int main(int argc, char** argv)
{
    string tableNameResident = "Residents";
    string tableNameRooms = "Rooms";

    Room room(tableNameRooms);
    room.createTableRoom(); // Stworzenie tabeli przy uruchomieniu programu. Jezeli juz istnieje to lepiej zakomentowac

    Resident resident(tableNameResident);
    resident.createTableResident(); // Stworzenie tabeli przy uruchomieniu programu. Jezeli juz istnieje to lepiej zakomentowac

    Interface i1;
	int decision{};
    i1.welcomePage();
	while (true)
	{
		while (true)
		{
			decision = i1.pageWhenUCanLoginOrRegisterOrExit(); //ekran wyboru: 1 - logowanie, 2 - rejestracja, 3 - wyjscie
			if (decision == 1)
			{
				cout << "logowanie";
			}
			else if (decision == 2)
			{
				cout << "rejestracja";
			}
			else
			{
				return 0;
			}
		}
	}

	return 0;
    
}