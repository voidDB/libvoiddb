#include "../include/common.h"
#include "../include/cursor.h"
#include "../include/node.h"

#include "cursor.h"

int voiddb_cursor_get_next(VOIDDB_cursor *cursor, VOIDDB_slice *key,
			   VOIDDB_slice *value);

int voiddb_cursor_get_next_(VOIDDB_cursor *cursor, VOIDDB_slice *key,
			    VOIDDB_slice *value);
