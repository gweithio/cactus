#include <cactus/cactus.h>
#include <core/cmd.h>

#include <stdio.h>
#include <stdlib.h>

int run_cmd(sqlite3 *db, enum command_types const type,
	    char const *const second_arg)
{
	if (type == NONE)
		return 1;

	switch (type) {
	case CREATE:
		return note_insert(second_arg, db);
		break;
	case DELETE:
		return note_delete(atoi(second_arg), db);
		break;
	case DELETE_ALL:
		return note_delete_all(db);
		break;
	case GET:
		return note_get(atoi(second_arg), db);
		break;
	case GET_ALL:
		return note_get_all(db);
		break;
	case REFRESH:
		return note_refresh(db);
		break;
	default:
		return 1;
		break;
	}
	return 0;
}
