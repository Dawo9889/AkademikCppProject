#include "User.h"
User::User(string& name) {
	this->tableName = name;
}

int User::createTableUser() {
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
		"user_id INT PRIMARY KEY,"
		"login_name VARCHAR(20) NOT NULL,"
		"password_hash VARCHAR(250) NOT NULL,"
		"password_salt Varchar(100) NOT NULL,"
		"role TEXT NOT NULL,"
		"CHECK(role IN('admin', 'user'))"
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