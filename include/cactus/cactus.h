#ifndef CACTUS_HEADER
#define CACTUS_HEADER
#include <sqlite3.h>

int note_insert(char* text, sqlite3* db);
int note_delete(int id, sqlite3* db);

#endif
