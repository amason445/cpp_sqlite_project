#include "sqlite3/sqlite3.h"
#include <iostream>

//checks sqlite return code
void check_error_code(int rc, sqlite3* db) {
	if (rc) {
		// handle database errors
		std::cerr << "Database could not open:\n" << sqlite3_errmsg(db) << std::endl;

	}
	else {
		// notify the database was successfully opened
		std::cout << "The database was opened successfully!" << std::endl;

	}
}


int main() {

	// declare database pointer and return code
	sqlite3* db;
	int rc;

	// open the database
	rc = sqlite3_open("hello_db!.db", &db);

	check_error_code(rc, db);

	sqlite3_close(db);

	return 0;

}