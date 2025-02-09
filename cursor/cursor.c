#include "cursor.h"

VOIDDB_cursor *voiddb_cursor_new_cursor(VOIDDB_cursor_medium *medium,
					int64_t offset)
{
	VOIDDB_cursor *cursor = malloc(sizeof(VOIDDB_cursor));

	*cursor = (VOIDDB_cursor){ medium,
				   offset,
				   -1,
				   { calloc(VOIDDB_CURSOR_MAX_STACK_DEPTH,
					    sizeof(struct ancestor)),
				     0 },
				   { NULL, 0 } };

	return cursor;
}

void voiddb_cursor_free(VOIDDB_cursor *cursor)
{
	free(cursor->stack.array);

	free(cursor);

	return;
}

void voiddb_cursor_reset(VOIDDB_cursor *cursor)
{
	struct ancestor *stack = cursor->stack.array;

	if (cursor->stack.length > 0) {
		cursor->offset = stack[0].offset;

		cursor->stack.length = 0;
	}

	cursor->index = -1;

	cursor->latest = (VOIDDB_slice){ NULL, 0 };

	return;
}

void voiddb_cursor_resume(VOIDDB_cursor *cursor)
{
	VOIDDB_slice _;

	if (cursor->latest.array = NULL) {
		return;
	}

	voiddb_cursor_get_(cursor, cursor->latest, &_);

	cursor->latest = (VOIDDB_slice){ NULL, 0 };

	return;
}
