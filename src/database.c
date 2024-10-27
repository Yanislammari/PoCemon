#include <sqlite3.h>

sqlite3* init_database() {
    sqlite3* db;
    sqlite3_open("../db/pocemon_database.sqlite", &db);
    return db;
}
