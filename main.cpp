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
    room.createTableRoom();

    Resident resident(tableNameResident);
    resident.createTableResident(); // Stworzenie tabeli przy uruchomieniu programu. Jezeli juz istnieje to lepiej zakomentowac

    User user(tableNameUsers);
    user.createTableUser();

 /*   string username = "hubert";
    string mail = "chuj@gmail.com";
    string passowrd = "hubert";
    user.addUser(username, mail, passowrd);*/

    Interface i1(user, room, resident);
    i1.welcomePage();
    
	return 0;
}