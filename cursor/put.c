#include <errno.h>
#include <string.h>

#include "../include/common.h"
#include "../include/cursor.h"
#include "../include/node.h"

#include "cursor.h"

int voiddb_cursor_put_(VOIDDB_cursor_medium *medium, int64_t offset,
		       int64_t put_pointer, int64_t put_length,
		       VOIDDB_slice key,
		       // out
		       int64_t *pointer_0, int64_t *pointer_1,
		       VOIDDB_slice *promoted)
{
	VOIDDB_slice new_node_0;
	VOIDDB_slice new_node_1 = {};
	VOIDDB_slice old_node;
	int e;
	int64_t index;
	int64_t length;
	int64_t pointer;

	e = voiddb_cursor_get_node(medium, offset, true, &old_node);
	if (e != 0) {
		goto end;
	}

	voiddb_node_search(old_node, key, &index, &pointer, &length);

	if (pointer == 0) {
		voiddb_node_insert(old_node, index, put_pointer, 0, put_length,
				   key, medium->meta(), &new_node_0,
				   &new_node_1, promoted);

	} else if (length > 0) {
		medium->free(medium, pointer, length);

		goto fall;

	} else if (pointer == VOIDDB_CURSOR_TOMBSTONE) {
fall:
		voiddb_node_update(old_node, index, put_pointer, put_length,
				   medium->meta(), &new_node_0);

	} else {
		voiddb_cursor_put_(medium, pointer, put_pointer, put_length,
				   key, pointer_0, pointer_1, promoted);
		if (e != 0) {
			goto end;
		}

		if (*pointer_1 == 0) {
			voiddb_node_update(old_node, index, *pointer_0, 0,
					   medium->meta(), &new_node_0);

		} else {
			voiddb_node_insert(old_node, index, *pointer_0,
					   *pointer_1, 0, *promoted,
					   medium->meta(), &new_node_0,
					   &new_node_1, promoted);

			*pointer_1 = 0;
		}
	}

	*pointer_0 = medium->save(medium, new_node_0);

	if (new_node_1.array != NULL) {
		*pointer_1 = medium->save(medium, new_node_1);
	}

end:
	return e;
}

int voiddb_cursor_put(VOIDDB_cursor *cursor, VOIDDB_slice key,
		      VOIDDB_slice value)
{
	VOIDDB_slice _0;
	VOIDDB_slice _1;
	VOIDDB_slice new_node;
	VOIDDB_slice new_root;
	VOIDDB_slice promoted;
	int e;
	int64_t pointer_0;
	int64_t pointer_1 = 0;

	if (key.length == 0) {
		goto fall;

	} else if (key.length > VOIDDB_CURSOR_MAX_KEY_LENGTH) {
		goto fall;

	} else if (value.length == 0) {
		goto fall;

	} else if (value.length > VOIDDB_CURSOR_MAX_VALUE_LENGTH) {
fall:
		return EINVAL;
	}

	voiddb_cursor_reset(cursor);

	promoted = (VOIDDB_slice){ malloc(VOIDDB_NODE_MAX_KEY_LENGTH), 0 };

	e = voiddb_cursor_put_(cursor->medium, cursor->offset,
			       cursor->medium->save(cursor->medium, value),
			       value.length, key, &pointer_0, &pointer_1,
			       &promoted);
	if (e != 0) {
		goto end;
	}

	memcpy(cursor->latest.array, key.array, key.length);

	cursor->latest.length = key.length;

	if (pointer_1 == 0) {
		cursor->offset = pointer_0;

	} else {
		new_node = voiddb_node_new_node();

		voiddb_node_insert(new_node, 0, pointer_0, pointer_1, 0,
				   promoted, cursor->medium->meta(), &new_root,
				   &_0, &_1);

		cursor->offset = cursor->medium->save(cursor->medium, new_root);

		free(new_node.array);
	}

end:
	free(promoted.array);

	return e;
}
