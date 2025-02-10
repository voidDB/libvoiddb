#include <stdlib.h>
#include <string.h>

#include "../../../include/cursor.h"

VOIDDB_slice medium_meta();

int64_t medium_save(VOIDDB_cursor_medium *medium, VOIDDB_slice data);

VOIDDB_slice medium_load(VOIDDB_cursor_medium *medium, int64_t offset,
			 int64_t length);

void medium_free(VOIDDB_cursor_medium *, int64_t, int64_t);

VOIDDB_cursor_medium *new_medium();
