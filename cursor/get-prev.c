#include "get-prev.h"

int voiddb_cursor_get_prev(VOIDDB_cursor *cursor, VOIDDB_slice *key,
			   VOIDDB_slice *value)
{
	voiddb_cursor_resume(cursor);

	cursor->index--;

	return voiddb_cursor_get_prev_(cursor, key, value);
}

int voiddb_cursor_get_prev_(VOIDDB_cursor *cursor, VOIDDB_slice *key,
			    VOIDDB_slice *value)
{
	VOIDDB_slice node;
	int e;
	int64_t length;
	int64_t pointer;

	struct ancestor *stack = cursor->stack.array;

	if (cursor->index < 0 && cursor->stack.length == 0) {
		return VOIDDB_ERROR_NOT_FOUND;

	} else if (cursor->index < 0) {
		cursor->offset = stack[cursor->stack.length - 1].offset;

		cursor->index = stack[cursor->stack.length - 1].index;

		cursor->stack.length--;

		goto recur;
	}

	e = voiddb_cursor_get_node(cursor->medium, cursor->offset, false,
				   &node);
	if (e != 0) {
		return e;
	}

	if (cursor->index == VOIDDB_NODE_MAX_NODE_LENGTH) {
		cursor->index = voiddb_node_length(node);
	}

	voiddb_node_value_or_child(node, cursor->index, &pointer, &length);

	if (pointer == 0 || pointer == VOIDDB_CURSOR_TOMBSTONE) {
		cursor->index--;

		goto recur;

	} else if (length > 0) {
		*key = voiddb_node_key(node, cursor->index);

		*value = cursor->medium->load(cursor->medium, pointer, length);

		return 0;
	}

	stack[cursor->stack.length] =
		(struct ancestor){ cursor->offset, cursor->index };

	cursor->stack.length++;

	cursor->offset, cursor->index = pointer, VOIDDB_NODE_MAX_NODE_LENGTH;

	goto recur;

recur:
	return voiddb_cursor_get_prev_(cursor, key, value);
}
