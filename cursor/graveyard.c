#include "graveyard.h"

bool voiddb_cursor_is_graveyard(VOIDDB_slice node)
{
	int64_t _;
	int64_t index;
	int64_t pointer;

	for (index = 0; index <= voiddb_node_length(node); index++) {
		voiddb_node_value_or_child(node, index, &pointer, &_);

		if ((pointer & VOIDDB_CURSOR_GRAVEYARD) > 0) {
			continue;

		} else if (pointer == VOIDDB_CURSOR_TOMBSTONE) {
			continue;

		} else if (pointer == 0 && index == voiddb_node_length(node)) {
			continue;

		} else {
			return false;
		}
	}

	return true;
}
