#include "sqlite3/sqlite3.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <memory>

//checks sqlite return code
static void check_error_code(int rc, sqlite3* db, const char* errMsg = nullptr, const char* operation = "Operation") {
	if (rc != SQLITE_OK) {
		// notify that there were issues with the database operation
		std::cerr << operation << " was not successful:\n" << (errMsg ? errMsg : sqlite3_errmsg(db)) << std::endl;
		if (errMsg) {
			sqlite3_free((char*)errMsg);
		}
		sqlite3_close(db);
		exit(1);
	}
	else {
		// notify that database operation was successfully completed
		std::cout << operation << " was competed successfully!" << std::endl;
	}
}

//writes SQLite query values to vector of tuples
static int messages_callback_function(void* data, int numColumns, char** fieldValues, char** columnNames) {
	std::vector<std::string>* messages = static_cast<std::vector<std::string>*>(data);
	if (fieldValues[0]) {
		messages->push_back(fieldValues[0]);
	}
	return 0;
}

void writeVectorToTextFile(const std::unique_ptr<std::vector<std::string>>& dataPtr, const std::string& filename) {
	//check if the point is null
	if (!dataPtr) {
		std::cerr << "The data pointer is null." << std::endl;
		return;
	}
	
	// open file stream
	std::ofstream file(filename);

	//check if file is open
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}

	//write vector to file
	for (const auto& line : *dataPtr) {
		file << line << "\n";
	}
}

int main() {
	// declare database pointer and return code
	sqlite3* db;
	char* errMsg = nullptr;
	int rc;

	// open the database
	rc = sqlite3_open("hello_db!.db", &db);

	//checks if database is functioning
	check_error_code(rc, db, nullptr, "Opening database");

	//create messages table
	const char* createTableSQLite = "CREATE TABLE IF NOT EXISTS HWMessages (id INTEGER PRIMARY KEY, message TEXT);";
	rc = sqlite3_exec(db, createTableSQLite, nullptr, nullptr, &errMsg);
	check_error_code(rc, db, errMsg, "Creating table Hello World Messages");

	//inserts ten messages into the messages table
	const char* insertSQL = "INSERT INTO HWMessages (message) VALUES ('Hello World');";
	for (int i = 0; i <= 10; i++) {
		rc = sqlite3_exec(db, insertSQL, nullptr, nullptr, &errMsg);
		check_error_code(rc, db, errMsg, "Inserting messages into the Hello World table");
	}

	//declare output vector for query as vector of strings
	std::unique_ptr<std::vector<std::string>> output_vector = std::make_unique<std::vector<std::string>>();
	
	//selects the messages column and inserts them into the output vector
	const char* selectMessages = "SELECT message from HWMessages";
	rc = sqlite3_exec(db, selectMessages, messages_callback_function, output_vector.get(), &errMsg);
	check_error_code(rc, db, errMsg, "Selecting messages from the Hello World table");

	//writes output vector to text file
	writeVectorToTextFile(output_vector, "output_file.txt");

	//closes SQLite DB and terminates script
	sqlite3_close(db);
	return 0;
}