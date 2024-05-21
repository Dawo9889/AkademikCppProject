#include <iostream>
#include "sqlite/sqlite3.h"
#include <string>
#include "Mieszkaniec.h";
#include "Pokoj.h";
using namespace std;

int main(int argc, char** argv)
{
    string nazwaTabeliMieszkancy = "Mieszkancy";
    string nazwaTabeliPokoj = "Pokoje";

    Pokoj pokoj(nazwaTabeliPokoj);
    //pokoj.createTablePokoj(); // Stworzenie tabeli przy uruchomieniu programu. Jezeli juz istnieje to lepiej zakomentowac

    Mieszkaniec mieszkaniec(nazwaTabeliMieszkancy);
    //mieszkaniec.createTableMieszkaniec(); // Stworzenie tabeli przy uruchomieniu programu. Jezeli juz istnieje to lepiej zakomentowac

   

    
}