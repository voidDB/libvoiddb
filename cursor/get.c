#include "get.h"

int voiddb_cursor_get(VOIDDB_cursor *cursor, VOIDDB_slice key,
		      VOIDDB_slice *value)
{
	voiddb_cursor_reset(cursor);

	return voiddb_cursor_get_(cursor, key, value);
}

int voiddb_cursor_get_first(VOIDDB_cursor *cursor, VOIDDB_slice *key,
			    VOIDDB_slice *value)
{
	voiddb_cursor_reset(cursor);

	return voiddb_cursor_get_next(cursor, key, value);
}

int voiddb_cursor_get_last(VOIDDB_cursor *cursor, VOIDDB_slice *key,
			   VOIDDB_slice *value)
{
	voiddb_cursor_reset(cursor);

	cursor->index = VOIDDB_NODE_MAX_NODE_LENGTH;

	return voiddb_cursor_get_prev_(cursor, key, value);
}

int voiddb_cursor_get_(VOIDDB_cursor *cursor, VOIDDB_slice key,
		       // out
		       VOIDDB_slice *value)
{
	VOIDDB_slice node;
	int e;
	int64_t length;
	int64_t pointer;

	struct ancestor *stack = cursor->stack.array;

	e = voiddb_cursor_get_node(cursor->medium, cursor->offset, false,
				   &node);
	if (e != 0) {
		return e;
	}

	voiddb_node_search(node, key, &cursor->index, &pointer, &length);

	if (pointer == VOIDDB_CURSOR_TOMBSTONE) {
		goto fall;

	} else if (pointer == 0) {
fall:
		return VOIDDB_ERROR_NOT_FOUND;

	} else if (length > 0) {
		*value = cursor->medium->load(cursor->offset, cursor->index);

		return 0;
	}

	stack[cursor->stack.length] =
		(struct ancestor){ cursor->offset, cursor->index };

	cursor->stack.length++;

	cursor->offset = pointer;

	return voiddb_cursor_get_(cursor, key, value);
}
