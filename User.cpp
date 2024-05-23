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
		"user_id INTEGER PRIMARY KEY,"
		"username VARCHAR(20) NOT NULL,"
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

int User::addUser(string& username, string& email, string& password)
{
    if (isUserInDatabase(username) == 1) {
        cout << "!!! User already exists !!! " << endl;
        return 3; // User already exists
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
    string insertSQL = "INSERT INTO " + tableName + " (username, password_hash, password_salt, role) VALUES (?, ?, ?, ?)";
    result = sqlite3_prepare_v2(db, insertSQL.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        cout << "Application Error: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }

    string role = "admin";
    string password_salt = generateSalt(10);
    string password_hash = generateHash(password, password_salt);

    // Setting parameters with data
    result = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        cout << "Application Error: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }
    result = sqlite3_bind_text(stmt, 2, password_hash.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        cout << "Application Error: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }
    result = sqlite3_bind_text(stmt, 3, password_salt.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        cout << "Application Error: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }
    result = sqlite3_bind_text(stmt, 4, role.c_str(), -1, SQLITE_STATIC);
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


string User::generateSalt(size_t length)
{
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	const size_t max_index = sizeof(charset) - 1;

	std::string salt;
	salt.reserve(length);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, max_index);

	for (size_t i = 0; i < length; ++i) {
		salt += charset[dis(gen)];
	}

	return salt;
}
string User::retrieveSaltFromUser(string& username) 
{
	if (!(isUserInDatabase(username) == 1)) {
		cout << "!!! User does not exist !!! " << endl;
		return "";
	}

    sqlite3* db;
    sqlite3_stmt* stmt;
    std::string fileName = "Akademik.db";
    std::string password_salt;

    // Database Open
    int result = sqlite3_open(fileName.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cout << "Application error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return "";
    }

    // Prepare SQL Query 
    std::string selectSQL = "SELECT password_salt FROM " + tableName + " WHERE username = ?";
    result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cout << "Application error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return "";
    }

    // Associating a parameter with a username
    result = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        std::cout << "Application error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return "";
    }

    // Execute an Query
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        // Powi¹zanie parametru z nazw¹ u¿ytkownika
        const unsigned char* salt = sqlite3_column_text(stmt, 0);
        password_salt = std::string(reinterpret_cast<const char*>(salt));
    }
    else {
        std::cout << "Application error: " << sqlite3_errmsg(db) << std::endl;
    }

    // Finish an query and close connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return password_salt;

}
string User::generateHash(const string& password, const string& salt)
{
	
	string combined = password + salt;
	unsigned int hash = 0;

	for (char c : combined) {
		hash = hash * 31 + c; //simple hashing function
	}

	//confert hash to hex values
	std::stringstream ss;
	ss << std::hex << hash;
	return ss.str();
}


int User::isUserInDatabase(string& username)
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
	string selectSQL = "SELECT username FROM " + tableName + " Where username = ?";
	result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
	if (result != SQLITE_OK)
	{
		cout << "Application error: " << sqlite3_errmsg(db) << endl;
		sqlite3_close(db);
		return result;
	}

	// Setting param with username
	result = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		cout << "application error: " << sqlite3_errmsg(db) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	// Execution of the request
	result = sqlite3_step(stmt);
	int userExists = (result == SQLITE_ROW) ? 1 : 0;

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return userExists;
	
}