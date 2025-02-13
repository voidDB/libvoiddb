#include "cursor.h"

int voiddb_cursor_del_(VOIDDB_cursor *cursor)
{
	VOIDDB_slice new_node;
	VOIDDB_slice old_node;
	int e;
	int64_t i;
	int64_t length;
	int64_t pointer;

	struct ancestor *stack = cursor->stack.array;

	e = voiddb_cursor_get_node(cursor->medium, cursor->offset, true,
				   &old_node);
	if (e != 0) {
		goto end;
	}

	voiddb_node_value_or_child(old_node, cursor->index, &pointer, &length);

	cursor->medium->free(cursor->medium, pointer, length);

	voiddb_node_update(old_node, cursor->index, VOIDDB_CURSOR_TOMBSTONE, 0,
			   cursor->medium->meta(), &new_node);

	pointer = cursor->medium->save(cursor->medium, new_node);

	cursor->offset = pointer;

	for (i = cursor->stack.length - 1; i > -1; i--) {
		e = voiddb_cursor_get_node(cursor->medium, stack[i].offset,
					   true, &old_node);
		if (e != 0) {
			goto end;
		}

		voiddb_node_update(old_node, stack[i].index, pointer, 0,
				   cursor->medium->meta(), &new_node);

		pointer = cursor->medium->save(cursor->medium, new_node);

		stack[i].offset = pointer;
	}

end:
	return e;
}

int voiddb_cursor_del(VOIDDB_cursor *cursor)
{
	voiddb_cursor_resume(cursor);

	return voiddb_cursor_del_(cursor);
}
