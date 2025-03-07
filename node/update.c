#include "include.h"

#include "node.h"

void voiddb_node_update(VOIDDB_slice node, int64_t index, int64_t pointer,
			int64_t length, VOIDDB_slice metadata,
			// out
			VOIDDB_slice *new_node)
{
	*new_node =
		(VOIDDB_slice){ malloc(VOIDDB_PAGE_SIZE), VOIDDB_PAGE_SIZE };

	memcpy((*new_node).array, node.array, VOIDDB_PAGE_SIZE);

	if (length < 0) {
		voiddb_node_elem_set_pointer(voiddb_node_elem(*new_node, index),
					     pointer);

		voiddb_node_elem_set_extra_metadata(
			voiddb_node_elem(*new_node, index), metadata);

	} else {
		voiddb_node_set_value_or_child(*new_node, index, pointer,
					       length, metadata);
	}

	return;
}
