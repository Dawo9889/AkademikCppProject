#include "Resident.h"
Resident::Resident(string& name) {
	this->tableName = name;
}



int Resident::createTableResident()
{
	sqlite3* db;
	char* err = nullptr;

	string file_name = "Akademik.db";
	int result = sqlite3_open(file_name.c_str(), &db);
	if (result != SQLITE_OK)
	{
		cout << "Blad aplikacji:" << sqlite3_errmsg(db) << endl;
		return result;
	}

	string createTableSQL = "CREATE TABLE IF NOT EXISTS " + this->tableName + "("
		"pesel VARCHAR(11) PRIMARY KEY,"
		"first_name VARCHAR(30) NOT NULL,"
		"last_name VARCHAR(30) NOT NULL,"
		"email VARCHAR(40) NOT NULL,"
		"room_number VARCHAR(4),"
		"FOREIGN KEY (room_number) REFERENCES Room(room_number)"
		");";
	
	result = sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, &err);
	if (result != SQLITE_OK) {
		cout << "Blad aplikacji: " << err << endl;
		sqlite3_free(err);
		return result;
	}
	sqlite3_close(db);
	return 0;
}


int Resident::addResident(string& PESEL, string& firstName, string& lastName, string& email, int roomNumber)
{
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::string fileName = "Akademik.db";

    // Otwarcie bazy danych
    int result = sqlite3_open(fileName.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cout << "Application error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return result;
    }

    // Przygotowanie zapytania SQL do wstawienia nowego rezydenta
    std::string insertSQL = "INSERT INTO Residents (pesel, first_name, last_name, email, room_number) VALUES (?, ?, ?, ?, ?)";
    result = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cout << "Application Error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }

    // Ustawienie parametrów z danymi rezydenta
    result = sqlite3_bind_text(stmt, 1, PESEL.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        std::cout << "Application Error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }
    result = sqlite3_bind_text(stmt, 2, firstName.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        std::cout << "Application Error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }
    result = sqlite3_bind_text(stmt, 3, lastName.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        std::cout << "Application Error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }
    result = sqlite3_bind_text(stmt, 4, email.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        std::cout << "Application Error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }
    result = sqlite3_bind_int(stmt, 5, roomNumber);
    if (result != SQLITE_OK) {
        cout << "B³¹d aplikacji (bind_int): " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }

    // Wykonanie zapytania
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        std::cout << "Application Error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }

    // Zakoñczenie zapytania i zamkniêcie bazy danych
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 1; // Success
}
int Resident::deleteResident(string& PESEL)
{
    sqlite3* db;
    char* err = nullptr;

    string file_name = "Akademik.db";
    int result = sqlite3_open(file_name.c_str(), &db);
    if (result != SQLITE_OK)
    {
        cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
        return result;
    }

    string deleteSQL = "DELETE FROM Residents WHERE pesel = '" + PESEL + "'; ";

    result = sqlite3_exec(db, deleteSQL.c_str(), nullptr, nullptr, &err);
    if (result != SQLITE_OK)
    {
        cout << "Blad aplikacji : " << err << endl;
        sqlite3_free(err);
        return result;
    }
    sqlite3_close(db);
    return 0;
}
bool Resident::isResidentInDatabase(const string& identifier, bool searchByEmail) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::string fileName = "Akademik.db";

    int result = sqlite3_open(fileName.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cout << "Blad aplikacji: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string selectSQL;
    if (searchByEmail) {
        selectSQL = "SELECT 1 FROM " + this->tableName + " WHERE email = ?";
    }
    else {
        selectSQL = "SELECT 1 FROM " + this->tableName + " WHERE pesel = ?";
    }

    result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cout << "Blad aplikacji: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    result = sqlite3_bind_text(stmt, 1, identifier.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        std::cout << "Blad aplikacji: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    result = sqlite3_step(stmt);
    bool exists = (result == SQLITE_ROW);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return exists;
}
bool Resident::isAnyResidentInRoom(string& roomNumber)
{
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::string fileName = "Akademik.db";

    int result = sqlite3_open(fileName.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cout << "Blad aplikacji: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string selectSQL = "SELECT COUNT(*) FROM " + this->tableName + " WHERE room_number = ?";
    result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cout << "Blad aplikacji: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    result = sqlite3_bind_text(stmt, 1, roomNumber.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        std::cout << "Blad aplikacji: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    int count = 0;
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    else {
        std::cout << "Blad aplikacji: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    if (count == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Resident::displayAllResidents()
{
    sqlite3* db;
    sqlite3_stmt* stmt;
    string fileName = "Akademik.db";

    // Otwarcie bazy danych
    int result = sqlite3_open(fileName.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cout << "Application error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Przygotowanie zapytania SQL do pobrania wszystkich pokoi i ich zawartoœci oraz mieszkañców
    std::string selectSQL = "SELECT * FROM Residents;";

    result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cout << "Application error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }


    // Wykonanie zapytania i pobranie wyników
    while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::string pesel = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string first_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string last_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        std::string room_number = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        std::cout << "  --------------------------------------" << std::endl;
        std::cout << " | PESEL: " << pesel << "\n";
        std::cout << " | Imie: " << first_name << "\n";
        std::cout << " | Nazwisko: " << last_name << "\n";
        std::cout << " | email: " << email << "\n";
        std::cout << " | Nr.pokoju: " << room_number << "\n";
        std::cout << "  --------------------------------------" << std::endl;
    }
    if (result == 0)
    {
        cout << "nic ni ma" << endl;;
    }
    // Zakoñczenie zapytania i zamkniêcie bazy danych
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
string Resident::returnRoomNumber(string& identifier, bool searchByPeselEmail)
{
    if (isResidentInDatabase(identifier, searchByPeselEmail)) {
        sqlite3* db;
        sqlite3_stmt* stmt;
        std::string fileName = "Akademik.db";
        std::string roomNumber = "";

        int result = sqlite3_open(fileName.c_str(), &db);
        if (result != SQLITE_OK) {
            std::cout << "Blad aplikacji: " << sqlite3_errmsg(db) << std::endl;
            return "";
        }
        std::string selectSQL;
        if (searchByPeselEmail) {
            selectSQL = "SELECT room_number FROM " + this->tableName + " WHERE email = ?";
        }
        else {
            selectSQL = "SELECT room_number FROM " + this->tableName + " WHERE pesel = ?";
        }
        
        result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
        if (result != SQLITE_OK) {
            std::cout << "Blad aplikacji: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return "";
        }

        result = sqlite3_bind_text(stmt, 1, identifier.c_str(), -1, SQLITE_STATIC);
        if (result != SQLITE_OK) {
            std::cout << "Blad aplikacji: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return "";
        }

        result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            roomNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return roomNumber;
    }
    return ""; // If resident is not found in the database
    
}
int Resident::changeRoomOfResitent(string& pesel,string& room_number)
{
    sqlite3* db;
    char* err = nullptr;

    string file_name = "Akademik.db";
    int result = sqlite3_open(file_name.c_str(), &db);
    if (result != SQLITE_OK)
    {
        cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
        return result;
    }

    string selectSQL = "UPDATE " + tableName + " SET room_number = '" + room_number + "' WHERE pesel = '" + pesel + "'; ";
    result = sqlite3_exec(db, selectSQL.c_str(), nullptr, nullptr, &err);

    if (result != SQLITE_OK)
    {
        cout << "Blad aplikacji:" << err << endl;
        sqlite3_free(err);
        return result;
    }
    sqlite3_close(db);
    return 0;
}