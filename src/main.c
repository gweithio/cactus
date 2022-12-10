#include <cactus/cactus.h>
#include <log.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// TODO: need to reason what we're gonna use this for
typedef enum { INSERT, GET, GETALL, DELETE, UPDATE } QUERY_TYPE;

static int
check_args(char *first, char *second)
{
  if (strcmp(first, second) == 0)
    return 1;

  return 0;
}

static int
create_empty_db(const char *name)
{
  struct stat buffer;
  char text_buffer[256];

  // using stat, we can check if the file exists
  if (stat(name, &buffer) == 0) {
    return 0;
  }

  FILE *db_file = fopen(name, "w");

  if (!db_file) {
    fclose(db_file);
    return 1;
  }

  fclose(db_file);
  return 0;
}

int
main(int argc, char **argv)
{
  sqlite3 *db;

  // I'M AN IDIOT!
  create_empty_db("notes.db");

  if (argc < 2) {
    printf("Usage: %s new 'Note Text!'\n", argv[0]);
    return 1;
  }

  // DB SETUP
  // TODO: We probably want to create the DB if it does not exist?
  if (sqlite3_open_v2("notes.db", &db, SQLITE_OPEN_READWRITE, NULL)
      != SQLITE_OK) {
    log_error("Could not open database: %s", sqlite3_errmsg(db));
    return 1;
  }

  if (sqlite3_exec(db,
                   "CREATE TABLE IF NOT EXISTS notes (id INTEGER PRIMARY KEY "
                   "AUTOINCREMENT, "
                   "text TEXT NOT NULL, "
                   "created_at DATETIME NOT NULL)",
                   NULL, NULL, NULL)
      != SQLITE_OK) {
    log_error("Could not create table: %s", sqlite3_errmsg(db));
    return 1;
  }

  // DB SETUP END

  // ACTIONS

  // TODO: clean this heap of trash code, switch statement maybe? or a
  // function?

  if (check_args(argv[1], "new")) {
    if (argc < 3) {
      printf("Usage: %s new 'Note Text!'\n", argv[0]);
      return 0;
    }
    if (note_insert(argv[2], db) != SQLITE_OK) {
      log_error("Could not insert row: %s", sqlite3_errmsg(db));
      return 1;
    } else {
      printf("Inserted row\n");
    }
  } else if (check_args(argv[1], "delete")) {
    if (argc < 3) {
      printf("Usage: %s delete <id>\n", argv[0]);
      return 1;
    }
    if (note_delete(atoi(argv[2]), db) != SQLITE_OK) {
      log_error("Could not delete row: %s", sqlite3_errmsg(db));
      return 1;
    } else {
      printf("Deleted row %d\n", atoi(argv[2]));
    }
  } else if (check_args(argv[1], "delete-all")) {
    if (note_delete_all(db) != SQLITE_OK) {
      log_error("Could not delete all notes\n");
      return 1;
    } else {
      printf("Deleted All Notes\n");
    }
  } else if (check_args(argv[1], "get")) {
    if (argc < 3) {
      printf("Usage: %s get <id>\n", argv[0]);
      return 1;
    }
    if (note_get(atoi(argv[2]), db) != SQLITE_OK) {
      log_error("Could not get row: %s", sqlite3_errmsg(db));
      return 1;
    } else {
      printf("Got row %d\n", atoi(argv[2]));
    }
  } else if (check_args(argv[1], "update")) {
    if (argc < 4) {
      printf("Usage: %s update <id> 'Note Text!'\n", argv[0]);
      return 1;
    }
    if (note_update(atoi(argv[2]), argv[3], db) != SQLITE_OK) {
      log_error("Could not update row: %s", sqlite3_errmsg(db));
      return 1;
    } else {
      printf("Updated row %d\n", atoi(argv[2]));
    }
  } else if (check_args(argv[1], "get-all")) {
    if (note_get_all(db) != SQLITE_OK) {
      log_error("Could not get all rows: %s", sqlite3_errmsg(db));
      return 1;
    } else {
      printf("Got all rows\n");
    }
  } else {
    printf("Unknown action: %s\n", argv[1]);
    return 1;
  }

  // ACTIONS END

  if (sqlite3_close(db) != SQLITE_OK) {
    log_error("Could not close database: %s", sqlite3_errmsg(db));
    return 1;
  }

  return 0;
}
