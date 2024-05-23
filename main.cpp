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

    string username = "DawidGala1";
    string mail = "Dawid@gmail.com";
    string passowrd = "password";
    user.addUser(username, mail, passowrd);
    cout<< user.retrieveSaltFromUser(username);
    
    //Interface i1;

    //i1.welcomePage();
    //i1.pageWhenUCanLoginOrRegisterOrExit();

    
}