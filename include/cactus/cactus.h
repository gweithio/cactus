#ifndef CACTUS_HEADER
#define CACTUS_HEADER
#include <sqlite3.h>
#include <stdint.h>

/*
 * Inserts a note using the text parameter, and setting its date to now
 *
 * @param text - the note text we want to insert
 * @param db - the db instance we're inserting to
 * @returns success */
uint8_t note_insert(char* text, sqlite3* db);

/*
 * Deletes a note from the db instance, using the id
 *
 * @param id - the id of the note we want to delete
 * @param db - the db instance we're delete from
 * @returns success (0) or failure (1) */
uint8_t note_delete(int id, sqlite3* db);

/*
 * Deletes all the notes, flushing out the DB of notes
 *
 * @params db - the db instance we're deleting all notes from
 * @returns success (0) or failure (1) */
uint8_t note_delete_all(sqlite3* db);

/*
 * gets a specific note based on the id
 *
 * @param id - the id of the note we want to get
 * @param db - the db instance were getting the data from
 * @returns success (0) or failure (1) */
uint8_t note_get(int id, sqlite3* db);

/*
 * gets a specific note based on the id
 *
 * @param id - the id of the note we want to update
 * @param text - the text we are replacing it with
 * @param db - the database instance we want to update
 * @returns success (0) or failure (1) */
uint8_t note_update(int id, char* text, sqlite3* db);

/*
 * get all notes in the db instance
 *
 * @param db - the db instance were getting all notes from
 * @returns success (0) or failure (1) */
uint8_t note_get_all(sqlite3* db);

#endif
