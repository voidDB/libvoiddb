#include "../include/common.h"
#include "../include/cursor.h"

#include "cursor.h"
#include "get-next.h"
#include "get-node.h"
#include "get-prev.h"

int voiddb_cursor_get_(VOIDDB_cursor *cursor, VOIDDB_slice key,
		       // out
		       VOIDDB_slice *value);
