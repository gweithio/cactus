#ifndef CMD_HEADER
#define CMD_HEADER

#include <sqlite3.h>
#include <cactus/cactus.h>

enum command_types { CREATE, DELETE, GET, GET_ALL, DELETE_ALL, REFRESH, NONE };

/**
 *  Were gonna want to create a function that takes in a argument compares it
 *  an runs the correct function
 */

int run_cmd(sqlite3 *db, struct failure_report report,
	    enum command_types const type, char const *const second_arg);

#endif
