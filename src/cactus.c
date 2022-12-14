#include <cactus/cactus.h>
#include <core/utils.h>

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int get_callback(void *data, int argc, char **argv, char **columnName)
{
	(void)data;
	for (int i = 0; i < argc; i++) {
		printf("%s = %s\n", columnName[i], argv[i] ? argv[i] : "NULL");
	}

	return 0;
}

uint8_t note_insert(char *text, sqlite3 *db)
{
	char *sql =
		"INSERT INTO notes (note_text, note_created_at) VALUES ('%s', '%s')";

	const char *time = time_now();
	char insert_string[256];
	printf("Noted (%s) created @ %s\n", text, time);

	sprintf(insert_string, sql, text, time);

	printf("SQL: %s\n", insert_string);

	return sqlite3_exec(db, insert_string, NULL, NULL, NULL);
}

uint8_t note_delete(int id, sqlite3 *db)
{
	char delete_string[256];
	sprintf(delete_string, "DELETE FROM notes WHERE id = %d", id);

	return sqlite3_exec(db, delete_string, NULL, NULL, NULL);
}

uint8_t note_delete_all(sqlite3 *db)
{
	char delete_all_string[256];

	sprintf(delete_all_string, "DELETE FROM notes");

	return sqlite3_exec(db, delete_all_string, NULL, NULL, NULL);
}

uint8_t note_get(int id, sqlite3 *db)
{
	char get_string[256];
	char *errorMesg = 0;
	sprintf(get_string, "SELECT * FROM notes WHERE id = %d", id);

	uint8_t rec = (uint8_t)sqlite3_exec(db, get_string, get_callback, NULL,
					    &errorMesg);

	if (rec != SQLITE_OK) {
		fprintf(stderr, "Error: %s\n", errorMesg);
		sqlite3_free(errorMesg);
	}

	return rec;
}

uint8_t note_update(int id, char *text, sqlite3 *db)
{
	char update_string[256];
	sprintf(update_string, "UPDATE notes SET text = '%s' WHERE id = %d",
		text, id);
	return sqlite3_exec(db, update_string, NULL, NULL, NULL);
}

uint8_t note_get_all(sqlite3 *db)
{
	char get_all_string[256];
	char *errorMesg = 0;

	sprintf(get_all_string, "SELECT * FROM notes");

	uint8_t rc = sqlite3_exec(db, get_all_string, get_callback, NULL,
				  &errorMesg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "Failed to get all rows\n");
		sqlite3_free(errorMesg);
	}

	return rc;
}

uint8_t note_refresh(sqlite3 *db)
{
	return remove("notes.db");
}
