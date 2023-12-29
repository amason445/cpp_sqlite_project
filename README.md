# C++ SQLite Project
## Project Summary
I started a project to build and manipulate a SQLite database with C++. Right now, it generates a SQLite file and then it creates a table called "HWMessages" where each row contains a primary integer key and the string message "Hello World." This script uses the SQLite3 library and the C Style API. It uses the UTF-8 functions and it also uses the `sqlite3_exec()` wrapper to execute queries. Currently, the main script just selects all of these "Hello World" messages and writes them to a text file called `output_file.txt`.

## Technology
- [SQLite Database and API](https://www.sqlite.org/index.html]
- C++

## Output Screenshots
Below are two screenshots that show the output database:

![alt text](https://github.com/amason445/cpp_sqlite_project/blob/master/Screenshots/Screenshot1.png)

![alt text](https://github.com/amason445/cpp_sqlite_project/blob/master/Screenshots/Screenshot2.png)

## Future Ideas
- Build into an ORM with OOP
- Build more tables and structure
- Run more complex queries
- Load in input data
