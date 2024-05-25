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
		return 0; // Pokój ju¿ istnieje
	}

	sqlite3* db;
	sqlite3_stmt* stmt;
	string fileName = "Akademik.db";
	int result = sqlite3_open(fileName.c_str(), &db);
	if (result != SQLITE_OK) {
		cout << "B³¹d aplikacji: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	// Dodawanie nowego pokoju
	string tableName = "rooms"; // Upewnij siê, ¿e nazwa tabeli jest poprawna
	string insertSQL = "INSERT INTO " + tableName + " (room_number, number_of_beds, is_available) VALUES (?, ?, ?)";
	result = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK) {
		cout << "B³¹d aplikacji (prepare): " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	// Ustawianie parametrów z danymi
	result = sqlite3_bind_text(stmt, 1, room_number.c_str(), -1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		cout << "B³¹d aplikacji (bind_text): " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_bind_int(stmt, 2, number_of_beds);
	if (result != SQLITE_OK) {
		cout << "B³¹d aplikacji (bind_int): " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_bind_int(stmt, 3, is_available ? 1 : 0);
	if (result != SQLITE_OK) {
		cout << "B³¹d aplikacji (bind_int): " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		cout << "B³¹d aplikacji (step): " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 1; // Sukces
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
int Room::deleteRoom(string & roomNumber)
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

	string deleteSQL = "DELETE FROM Rooms WHERE room_number = " + roomNumber + "; ";

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

bool Room::isRoomAvailable(string& roomNumber)
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	string fileName = "Akademik.db";
	int result = sqlite3_open(fileName.c_str(), &db);
	if (result != SQLITE_OK) {
		cout << "Application error: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return false;
	}

	string selectSQL = "SELECT is_available FROM " + tableName + " WHERE room_number = ?";
	result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK) {
		cout << "Application error: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return false;
	}

	sqlite3_bind_text(stmt, 1, roomNumber.c_str(), -1, SQLITE_STATIC);

	bool isAvailable = false;
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		isAvailable = sqlite3_column_int(stmt, 0);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return isAvailable;
}

bool Room::updateRoomAvailability(string& roomNumber)
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	string fileName = "Akademik.db";
	int result = sqlite3_open(fileName.c_str(), &db);
	if (result != SQLITE_OK) {
		cout << "Application error: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return false;
	}

	// count resident amounts in that room
	string countSQL = "SELECT COUNT(*) FROM Residents WHERE room_number = ?";
	result = sqlite3_prepare_v2(db, countSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK) {
		cout << "Application error: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return false;
	}

	sqlite3_bind_text(stmt, 1, roomNumber.c_str(), -1, SQLITE_STATIC);

	int numberOfResidents = 0;
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		numberOfResidents = sqlite3_column_int(stmt, 0);
	}
	sqlite3_finalize(stmt);

	// Count bed amounts in that room
	string bedsSQL = "SELECT number_of_beds FROM " + tableName + " WHERE room_number = ?";
	result = sqlite3_prepare_v2(db, bedsSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK) {
		cout << "Application error: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return false;
	}

	sqlite3_bind_text(stmt, 1, roomNumber.c_str(), -1, SQLITE_STATIC);

	int numberOfBeds = 0;
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		numberOfBeds = sqlite3_column_int(stmt, 0);
	}
	sqlite3_finalize(stmt);

	// Updating room availability
	bool isAvailable = (numberOfResidents < numberOfBeds);
	string updateSQL = "UPDATE " + tableName + " SET is_available = ? WHERE room_number = ?";
	result = sqlite3_prepare_v2(db, updateSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK) {
		cout << "Application error: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return false;
	}

	sqlite3_bind_int(stmt, 1, isAvailable);
	sqlite3_bind_text(stmt, 2, roomNumber.c_str(), -1, SQLITE_STATIC);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		cout << "Application error: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return false;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return true;
}

void Room::displayAllRooms() 
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	string fileName = "Akademik.db";

	
	int result = sqlite3_open(fileName.c_str(), &db);
	if (result != SQLITE_OK) {
		std::cout << "Application error: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}

	// Przygotowanie zapytania SQL do pobrania wszystkich pokoi i ich zawartoœci oraz mieszkañców
	std::string selectSQL =
		"SELECT r.room_number, r.number_of_beds, r.is_available, res.pesel, res.first_name, res.last_name, res.email "
		"FROM Rooms r "
		"LEFT JOIN Residents res ON r.room_number = res.room_number;";

	result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK) {
		std::cout << "Application error: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}

	std::string currentRoom = "";
	bool firstRoom = true;

	// Wykonanie zapytania i pobranie wyników
	while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
		std::string roomNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		int numberOfBeds = sqlite3_column_int(stmt, 1);
		bool isAvailable = sqlite3_column_int(stmt, 2);
		const unsigned char* peselText = sqlite3_column_text(stmt, 3);
		const unsigned char* firstNameText = sqlite3_column_text(stmt, 4);
		const unsigned char* lastNameText = sqlite3_column_text(stmt, 5);
		const unsigned char* emailText = sqlite3_column_text(stmt, 6);

		if (roomNumber != currentRoom) {
			if (!firstRoom) {
				std::cout << "\n";
			}
			currentRoom = roomNumber;
			firstRoom = false;
			std::cout << "  --------------------------------------" << std::endl;
			std::cout << " | Room Number: " << roomNumber << "\n";
			std::cout << " | Number of Beds: " << numberOfBeds << "\n";
			std::cout << " | Is Available: " << (isAvailable ? "Yes" : "No") << "\n";
			std::cout << " | Residents:\n";
		}
		
		if (peselText) {
			std::string firstName = reinterpret_cast<const char*>(firstNameText);
			std::string lastName = reinterpret_cast<const char*>(lastNameText);
			std::string email = reinterpret_cast<const char*>(emailText);

			std::cout << " |	First Name: " << firstName << "\n";
			std::cout << " |	Last Name: " << lastName << "\n";
			std::cout << " |	Email: " << email << "\n";
		}
		std::cout << "  --------------------------------------" << std::endl;
	}

	// Zakoñczenie zapytania i zamkniêcie bazy danych
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

