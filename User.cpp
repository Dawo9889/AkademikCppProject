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
		"email Varchar(100) NOT NULL,"
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
        return 0; // User already exists
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
    string insertSQL = "INSERT INTO " + tableName + " (username, password_hash, password_salt, email, role) VALUES (?, ?, ?, ?, ?)";
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
    result = sqlite3_bind_text(stmt, 4, email.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        cout << "Application Error: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }
    result = sqlite3_bind_text(stmt, 5, role.c_str(), -1, SQLITE_STATIC);
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
    const size_t max_index = sizeof(charset) - 1; // Size of charset 

    string salt;
    salt.reserve(length); // Reserve space for efficiency

    random_device rd; // Obtain a random number from hardware
    mt19937 gen(rd()); // Seed the generator
    uniform_int_distribution<> dis(0, max_index - 1); // Define the range

    for (size_t i = 0; i < length; ++i) {
        salt += charset[dis(gen)]; // Append a random character from charset
    }

    return salt; // Return the generated salt
}
string User::generateHash(const string& password, const string& salt)
{
	
	string combined = password + salt;
	unsigned long hash = 0;

	for (char c : combined) {
		hash = hash * 31 + c; //simple hashing function
	}

	//confert hash to hex values
	stringstream ss;
	ss << hex << hash;
	return ss.str();
}

bool User::validateCredentials(string& username, string& password)
{
    UserCredentials userCredentials = getUserCredentials(username);
    if (userCredentials.username.empty()) {
        return false; // username not found
    }

    // generate hash based on retrived password from user and salt from database
    string generatedHash = generateHash(password, userCredentials.password_salt);

    // validating generated new hash to existed one in database
    return generatedHash == userCredentials.password_hash;
}

User::UserCredentials User::getUserCredentials(string& username)
{   sqlite3* db;
    sqlite3_stmt* stmt;
    UserCredentials userCredentials;
    string fileName = "Akademik.db";

    if (isUserInDatabase(username) != 1) {
        cout << "!!! User not found i the database, you should register first !!! " << endl;
        return userCredentials; // user not found
    }
    
    // database open
    int result = sqlite3_open(fileName.c_str(), &db);
    if (result != SQLITE_OK) {
        cout << "Application error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return userCredentials;
    }

    // Przygotowanie zapytania SQL do pobrania danych u¿ytkownika
    string selectSQL = "SELECT username, password_hash, password_salt FROM " + tableName + " WHERE username = ?";
    result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        cout << "Application error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return userCredentials;
    }

    // Powi¹zanie parametru z nazw¹ u¿ytkownika
    result = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        cout << "Application error: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return userCredentials;
    }

    // Wykonanie zapytania i pobranie wyników
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        userCredentials.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        userCredentials.password_hash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        userCredentials.password_salt = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    }
    else {
        cout << "Application error: " << sqlite3_errmsg(db) << endl;
    }

    // Zakoñczenie zapytania i zamkniêcie bazy danych
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return userCredentials;
}

string User::getEmailByLogin(const string& login)
{
    sqlite3* db;
    sqlite3_stmt* stmt;
    string fileName = "Akademik.db";
    string email;

    int result = sqlite3_open(fileName.c_str(), &db);
    if (result != SQLITE_OK) {
        cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
        return "";
    }

    string selectSQL = "SELECT email FROM " + this->tableName + " WHERE username = ?";
    result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return "";
    }

    result = sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        cout << "Blad aplikacji: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return "";
    }

    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }
    else {
        cout << "Nie znaleziono uzytkownika o podanym loginie." << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return email;
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

string User::getUserRole(const string& username) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    string role;
    string fileName = "Akademik.db";
    // open cdatabase
    int result = sqlite3_open(fileName.c_str(), &db);
    if (result != SQLITE_OK) {
        cout << "Application error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return role;
    }

    // prepare sql query
    string selectSQL = "SELECT role FROM " + tableName + " WHERE username = ?";
    result = sqlite3_prepare_v2(db, selectSQL.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        cout << "Application error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return role;
    }

    // Setting up param with username
    result = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    if (result != SQLITE_OK) {
        cout << "Application error: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return role;
    }

    // Execute an query
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    }
    else {
        cout << "Application error: " << sqlite3_errmsg(db) << endl;
    }

    // db connection close
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return role;
}
