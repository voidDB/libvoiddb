#include "include.h"

#include "node.h"

void voiddb_node_search(VOIDDB_slice node, VOIDDB_slice key,
			// out
			int64_t *index, int64_t *pointer, int64_t *length)
{
	int result = 0;

	for (*index = 0; *index < voiddb_node_length(node); (*index)++) {
		result = voiddb_common_compare(key,
					       voiddb_node_key(node, *index));

		if (result < 1) {
			break;
		}
	}

	voiddb_node_value_or_child(node, *index, pointer, length);

	if (*length > 0 && result == 0) {
		return;

	} else if (*length > 0) {
		*pointer = 0;

		*length = 0;
	}

	return;
}
