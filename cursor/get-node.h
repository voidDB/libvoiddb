#include "../node/include.h"

#include "include.h"

int voiddb_cursor_get_node(VOIDDB_cursor_medium *medium, int64_t offset,
			   bool free,
			   // out
			   VOIDDB_slice *node);
