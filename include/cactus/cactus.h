#ifndef CACTUS_HEADER
#define CACTUS_HEADER
#include <sqlite3.h>

int note_insert(char* text, sqlite3* db);
int note_delete(int id, sqlite3* db);
int note_get(int id, sqlite3* db);
int note_update(int id, char* text, sqlite3* db);
int note_get_all(sqlite3* db);

#endif
