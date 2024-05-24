#include "Room.h"
Room::Room(string& name) {
	this->tableName = name;
}

int Room::createTableRoom(){
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
		"room_number VARCHAR(4) PRIMARY KEY,"
		"number_of_beds TINYINT NOT NULL,"
		"is_available BOOL NOT NULL"
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
int Room::addRoom(string& room_number, int& number_of_beds, bool& is_available)
{
	if (isRoomInDatabase(room_number) == 1) {
		cout << "!!! Room already exists !!! " << endl;
		return 0;
	}

	sqlite3* db;
	sqlite3_stmt* stmt;
	string fileName = "Akademik.db";
	int result = sqlite3_open(fileName.c_str(), &db);
	if (result != SQLITE_OK) {
		cout << "Application error: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	// Adding new user
	string insertSQL = "INSERT INTO " + tableName + " (room_number, number_of_beds, is_available) VALUES (?, ?, ?)";
	result = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK) {
		cout << "Application Error: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;

		// Setting parameters with data
		result = sqlite3_bind_text(stmt, 1, room_number.c_str(), -1, SQLITE_STATIC);
		if (result != SQLITE_OK) {
			cout << "Application Error: " << sqlite3_errmsg(db) << endl;
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_int(stmt, 1, number_of_beds);
		if (result != SQLITE_OK) {
			cout << "Application Error: " << sqlite3_errmsg(db) << endl;
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_int(stmt, 1, is_available ? 1 : 0);
		if (result != SQLITE_OK) {
			cout << "Application Error: " << sqlite3_errmsg(db) << endl;
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			cout << "Application Error: " << sqlite3_errmsg(db) << endl;
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 1; // Success
	}
}
int Room::isRoomInDatabase(string& room_number)
{
	sqlite3* db;
	sqlite3_stmt* stmt;

	string fileName = "Akademik.db";
	int result = sqlite3_open(fileName.c_str(), &db);
	if (result != SQLITE_OK) {
		cout << "Application error: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	//Checking if user already exists
	string selectSQL = "SELECT room_number FROM " + tableName + " Where room_number = ?";
	result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK)
	{
		cout << "Application error: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	// Setting param with username
	result = sqlite3_bind_text(stmt, 1, room_number.c_str(), -1, SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		cout << "application error: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	// Execution of the request
	result = sqlite3_step(stmt);
	int roomExists = (result == SQLITE_ROW) ? 1 : 0;

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return roomExists;

}
