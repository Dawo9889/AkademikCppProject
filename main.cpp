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
    i1.welcomePage();

	return 0;
    
}