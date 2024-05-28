#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include "Resident.h";
#include "Room.h";
#include "User.h";
#include "Interface.h"
using namespace std;

int main(int argc, char** argv)
{
    string tableNameResident = "Residents";
    string tableNameRooms = "Rooms";
    string tableNameUsers = "Users";

    Room room(tableNameRooms);
    room.createTableRoom(); // Stworzenie tabeli przy uruchomieniu programu. Jezeli juz istnieje to lepiej zakomentowac

    Resident resident(tableNameResident);
    resident.createTableResident(); // Stworzenie tabeli przy uruchomieniu programu. Jezeli juz istnieje to lepiej zakomentowac

    User user(tableNameUsers);
    user.createTableUser(); // Stworzenie tabeli przy uruchomieniu programu. Jezeli juz istnieje to lepiej zakomentowac

    Interface i1(user, room, resident); //konstruktor interfejsu
    i1.mainMenu();
    
	return 0;
}