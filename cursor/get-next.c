#include "get-next.h"

int voiddb_cursor_get_next_(VOIDDB_cursor *cursor, VOIDDB_slice *key,
			    VOIDDB_slice *value)
{
	VOIDDB_slice node;
	int e;
	int64_t length;
	int64_t pointer;

	struct ancestor *stack = cursor->stack.array;

	if (cursor->index >= VOIDDB_NODE_MAX_NODE_LENGTH) {
		goto end;
	}

	e = voiddb_cursor_get_node(cursor->medium, cursor->offset, false,
				   &node);
	if (e != 0) {
		return e;
	}

	voiddb_node_value_or_child(node, cursor->index, &pointer, &length);

	if (length > 0) {
		*key = voiddb_node_key(node, cursor->index);

		*value = cursor->medium->load(cursor->medium, pointer, length);

		return 0;

	} else if (pointer == VOIDDB_CURSOR_TOMBSTONE) {
		cursor->index++;

		goto recur;

	} else if (pointer > 0) {
		stack[cursor->stack.length] =
			(struct ancestor){ cursor->offset, cursor->index };

		cursor->stack.length++;

		cursor->offset = pointer;

		cursor->index = 0;

		goto recur;
	}

end:
	if (cursor->stack.length > 0) {
		cursor->offset = stack[cursor->stack.length - 1].offset;

		cursor->index = stack[cursor->stack.length - 1].index + 1;

		cursor->stack.length--;

		goto recur;
	}

	return VOIDDB_ERROR_NOT_FOUND;

recur:
	return voiddb_cursor_get_next_(cursor, key, value);
}

int voiddb_cursor_get_next(VOIDDB_cursor *cursor, VOIDDB_slice *key,
			   VOIDDB_slice *value)
{
	voiddb_cursor_resume(cursor);

	cursor->index++;

	return voiddb_cursor_get_next_(cursor, key, value);
}
