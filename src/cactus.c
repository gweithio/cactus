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

int note_get(int id, sqlite3* db) {
  char get_string[256];
  sprintf(get_string, "SELECT * FROM notes WHERE id = %d", id);
  return sqlite3_exec(db, get_string, NULL, NULL, NULL);
}

int note_update(int id, char* text, sqlite3* db) {
  char update_string[256];
  sprintf(update_string, "UPDATE notes SET text = '%s' WHERE id = %d", text,
          id);
  return sqlite3_exec(db, update_string, NULL, NULL, NULL);
}

int note_get_all(sqlite3* db) {
  char get_all_string[256];
  sprintf(get_all_string, "SELECT * FROM notes");
  return sqlite3_exec(db, get_all_string, NULL, NULL, NULL);
}
