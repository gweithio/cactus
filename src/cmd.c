#include <cactus/cactus.h>
#include <core/cmd.h>

#include <stdio.h>
#include <stdlib.h>

int run_cmd(sqlite3 *db, struct failure_report report,
	    enum command_types const type, char const *second_arg)
{
	if (type == NONE)
		return 1;

	switch (type) {
	case CREATE:
		note_insert(second_arg, db, report);
		break;
	case DELETE:
		note_delete(atoi(second_arg), db, report);
		break;
	case DELETE_ALL:
		note_delete_all(db, report);
		break;
	case GET:
		note_get(atoi(second_arg), db, report);
		break;
	case GET_ALL:
		note_get_all(db, report);
		break;
	case REFRESH:
		note_refresh(db);
		break;
	default:
		return 1;
		break;
	}
	return 0;
}
