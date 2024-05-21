#include "Mieszkaniec.h"
Mieszkaniec::Mieszkaniec(string& name) {
	this->tableName = name;
}

int Mieszkaniec::createTableMieszkaniec()
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
		"PESEL VARCHAR(11) PRIMARY KEY,"
		"Imie VARCHAR(30) NOT NULL,"
		"Nazwisko VARCHAR(30) NOT NULL,"
		"Email VARCHAR(40) NOT NULL,"
		"nr_pokoju VARCHAR(4),"
		"FOREIGN KEY (nr_pokoju) REFERENCES pokoj(nr_pokoju)"
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