#include <cactus/cactus.h>
#include <core/cmd.h>

#include <log.h>

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static enum command_types
check_args(char *first)
{
  if (strcmp(first, "new") == 0) {
    return CREATE;
  } else if (strcmp(first, "delete") == 0) {
    return DELETE;
  } else if (strcmp(first, "get") == 0) {
    return GET;
  } else if (strcmp(first, "get-all") == 0) {
    return GET_ALL;
  } else if (strcmp(first, "delete-all") == 0) {
    return DELETE_ALL;
  } else if (strcmp(first, "refresh") == 0) {
    return REFRESH;

  } else {
    return NONE;
  }

  return 0;
}

static int
create_empty_db(const char *name)
{
  struct stat buffer;
  char text_buffer[256];

  // using stat, we can check if the file exists
  if (stat(name, &buffer) == 0) {
    return 1;
  }

  FILE *db_file = fopen(name, "w");

  if (!db_file) {
    fclose(db_file);
    return 0;
  }

  fclose(db_file);
  return 1;
}

static void
create_base_table(sqlite3 *db)
{
  if (sqlite3_exec(db,
                   "CREATE TABLE IF NOT EXISTS notes (id INTEGER PRIMARY KEY "
                   "AUTOINCREMENT, "
                   "note_text TEXT NOT NULL, "
                   "note_created_at DATETIME NOT NULL)",
                   NULL, NULL, NULL)
      != SQLITE_OK) {
    log_error("Could not create table: %s", sqlite3_errmsg(db));

    exit(EXIT_FAILURE);
  }
}

int
main(int argc, char **argv)
{
  sqlite3 *db;

  if (argc < 2) {
    printf("Usage: %s new 'Note Text!'\n", argv[0]);
    return 1;
  }

  if (!create_empty_db("notes.db")) {
    log_error("Failed to create empty db");
    return 1;
  }

  // DB SETUP
  if (sqlite3_open_v2("notes.db", &db, SQLITE_OPEN_READWRITE, NULL)
      != SQLITE_OK) {
    log_error("Could not open database: %s", sqlite3_errmsg(db));
    return 0;
  }

  create_base_table(db);

  if (sqlite3_close(db) != SQLITE_OK) {
    log_error("Could not close database: %s", sqlite3_errmsg(db));
    return 0;
  }

  if (run_cmd(db, check_args(argv[1]), argv[2]) != SQLITE_OK) {
    log_error("Failed to run command: %s", sqlite3_errmsg(db));
    return 0;
  } else {
    return 1;
  }
}
