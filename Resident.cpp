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

bool Resident::isResidentInDatabase(string& PESEL) 
{
    sqlite3* db;
    sqlite3_stmt* stmt;
    std::string fileName = "Akademik.db";

    int result = sqlite3_open(fileName.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cout << "Blad aplikacji: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string selectSQL = "SELECT 1 FROM " + this->tableName + " WHERE pesel = ?";
    result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cout << "Blad aplikacji: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    result = sqlite3_bind_text(stmt, 1, PESEL.c_str(), -1, SQLITE_STATIC);
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