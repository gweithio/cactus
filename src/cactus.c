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

void note_insert(char const *const text, sqlite3 *db,
		 struct failure_report report)
{
	char *sql =
		"INSERT INTO notes (note_text, note_created_at) VALUES ('%s', '%s')";

	char *const time = time_now();
	char insert_string[256];
	char *errorMsg = 0;
	printf("Noted (%s) created @ %s\n", text, time);

	sprintf(insert_string, sql, text, time);

	// NOTE(ethan): This is the big thats failing
	uint8_t result = sqlite3_exec(db, insert_string, NULL, NULL, &errorMsg);

	if (result != SQLITE_OK) {
		sprintf(report.reason, "Failed to insert string\n");
		report.sqlReason = errorMsg;
	}

	free(time);
}

void note_delete(int id, sqlite3 *db, struct failure_report report)
{
	char delete_string[256];
	char *errorMsg = 0;
	sprintf(delete_string, "DELETE FROM notes WHERE id = %d", id);

	uint8_t result = sqlite3_exec(db, delete_string, NULL, NULL, &errorMsg);

	if (result != SQLITE_OK) {
		sprintf(report.reason, "Failed to delete note: %d\n", id);
		report.sqlReason = errorMsg;
	}
}

void note_delete_all(sqlite3 *db, struct failure_report report)
{
	char delete_all_string[256];
	char *errorMsg = 0;

	sprintf(delete_all_string, "DELETE FROM notes");
	uint8_t result =
		sqlite3_exec(db, delete_all_string, NULL, NULL, &errorMsg);

	if (result != SQLITE_OK) {
		sprintf(report.reason, "Failed to delete all notes\n");
		report.sqlReason = errorMsg;
	}
}

void note_get(int id, sqlite3 *db, struct failure_report report)
{
	char get_string[256];
	char *errorMsg = 0;
	sprintf(get_string, "SELECT * FROM notes WHERE id = %d", id);

	uint8_t result =
		sqlite3_exec(db, get_string, get_callback, NULL, &errorMsg);

	if (result != SQLITE_OK) {
		sprintf(report.reason, "Failed to get note: %d\n", id);
		report.sqlReason = errorMsg;
	}
}

void note_update(int id, char const *const text, sqlite3 *db,
		 struct failure_report report)
{
	char update_string[256];
	char *errorMsg = 0;
	sprintf(update_string, "UPDATE notes SET text = '%s' WHERE id = %d",
		text, id);
	uint8_t result = sqlite3_exec(db, update_string, NULL, NULL, &errorMsg);

	if (result != SQLITE_OK) {
		sprintf(report.reason, "Error: %s\n", errorMsg);
		report.sqlReason = errorMsg;
	}
}

void note_get_all(sqlite3 *db, struct failure_report report)
{
	char get_all_string[256];
	char *errorMsg = 0;

	sprintf(get_all_string, "SELECT * FROM notes");

	uint8_t result =
		sqlite3_exec(db, get_all_string, get_callback, NULL, &errorMsg);

	if (result != SQLITE_OK) {
		sprintf(report.reason, "Failued to get all rows\n");
		report.sqlReason = errorMsg;
	}
}

void note_refresh(sqlite3 *db)
{
	remove("notes.db");
}
