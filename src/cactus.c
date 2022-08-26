#include <log.h>
#include <cactus/cactus.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cactus/base.h>
#include <string.h>

static int get_callback(void* data, int argc, char** argv, char** columnName) {
  fprintf(stderr, "%s\n", (const char*)data);

  for (int i = 0; i < argc; i++) {
    printf("%s = %s\n", columnName[i], argv[i] ? argv[i] : "NULL");
  }

  return 0;
}

int note_insert(char* text, sqlite3* db) {
  char*       sql  = "INSERT INTO notes (text, created_at) VALUES ('%s', '%s')";
  const char* time = time_now();
  char        insert_string[256];

  sprintf(insert_string, sql, text, time);

  printf("%s\n", insert_string);

  return sqlite3_exec(db, insert_string, NULL, NULL, NULL);
}

int note_delete(int id, sqlite3* db) {
  char delete_string[256];
  sprintf(delete_string, "DELETE FROM notes WHERE id = %d", id);

  return sqlite3_exec(db, delete_string, NULL, NULL, NULL);
}

int note_get(int id, sqlite3* db) {
  char        get_string[256];
  const char* data      = "Callback function called";
  char*       errorMesg = 0;
  sprintf(get_string, "SELECT * FROM notes WHERE id = %d", id);

  int rec = sqlite3_exec(db, get_string, get_callback, (void*)data, &errorMesg);

  if (rec != SQLITE_OK) {
    fprintf(stderr, "Error: %s\n", errorMesg);
    sqlite3_free(errorMesg);
  }

  return rec;
}

int note_update(int id, char* text, sqlite3* db) {
  char update_string[256];
  sprintf(update_string, "UPDATE notes SET text = '%s' WHERE id = %d", text,
          id);
  return sqlite3_exec(db, update_string, NULL, NULL, NULL);
}

int note_get_all(sqlite3* db) {
  char        get_all_string[256];
  const char* data      = "Callback function called";
  char*       errorMesg = 0;

  sprintf(get_all_string, "SELECT * FROM notes");

  int rc =
      sqlite3_exec(db, get_all_string, get_callback, (void*)data, &errorMesg);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to get all rows\n");
    sqlite3_free(errorMesg);
  }

  return rc;
}
