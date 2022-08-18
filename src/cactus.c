#include <log.h>
#include <cactus/cactus.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cactus/base.h>
#include <string.h>

int note_insert(char* text, sqlite3* db) {
  char* sql = "INSERT INTO notes (text, created_at) VALUES ('%s', %s)";

  char insert_string[strlen(sql) + strlen(text)];

  sprintf(insert_string, sql, text, "2022-08-18");

  return sqlite3_exec(db, insert_string, NULL, NULL, NULL);
}

int note_delete(int id, sqlite3* db) {
  char delete_string[256];
  sprintf(delete_string, "DELETE FROM notes WHERE id = %d", id);

  return sqlite3_exec(db, delete_string, NULL, NULL, NULL);
}
