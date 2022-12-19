#ifndef CACTUS_HEADER
#define CACTUS_HEADER

#include <sqlite3.h>

#include <stdint.h>

struct failure_report {
	char *const reason;
	char *sqlReason;
};

/*
 * Inserts a note using the text parameter, and setting its date to now
 *
 * @param text - the note text we want to insert
 * @param db - the db instance we're inserting to
 *
 * */
void note_insert(char const *const text, sqlite3 *db,
		 struct failure_report report);

/*
 * Deletes a note from the db instance, using the id
 *
 * @param id - the id of the note we want to delete
 * @param db - the db instance we're delete from
 * 
 * */
void note_delete(int id, sqlite3 *db, struct failure_report report);

/*
 * Deletes all the notes, flushing out the DB of notes
 *
 * @params db - the db instance we're deleting all notes from
 */
void note_delete_all(sqlite3 *db, struct failure_report report);

/*
 * gets a specific note based on the id
 *
 * @param id - the id of the note we want to get
 * @param db - the db instance were getting the data from
 *  */
void note_get(int id, sqlite3 *db, struct failure_report report);

/*
 * gets a specific note based on the id
 *
 * @param id - the id of the note we want to update
 * @param text - the text we are replacing it with
 * @param db - the database instance we want to update
 * */
void note_update(int id, char const *const text, sqlite3 *db,
		 struct failure_report report);

/*
 * get all notes in the db instance
 *
 * @param db - the db instance were getting all notes from
 *  */
void note_get_all(sqlite3 *db, struct failure_report report);

/*
 * refreshes the db instance by deleting the db
 *
 * @param db - the db instance were removing
 *  */
void note_refresh(sqlite3 *db);

#endif
