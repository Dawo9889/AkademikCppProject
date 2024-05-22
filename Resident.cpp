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