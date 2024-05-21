#include "Pokoj.h"
Pokoj::Pokoj(string& name) {
	this->tableName = name;
}

int Pokoj::createTablePokoj(){
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
		"nr_pokoju VARCHAR(4) PRIMARY KEY,"
		"ilosc_miejsc TINYINT NOT NULL,"
		"dostep BOOL NOT NULL"
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