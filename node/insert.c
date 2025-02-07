#include "../include/node.h"

#include "copy.h"
#include "node.h"

void voiddb_node_split(VOIDDB_slice node,
		       // out
		       VOIDDB_slice *new_node_l, VOIDDB_slice *new_node_r,
		       VOIDDB_slice *promoted)
{
	int i;
	int shift = -VOIDDB_NODE_MAX_NODE_LENGTH / 2;

	*new_node_l = voiddb_node_new_node();
	*new_node_r = voiddb_node_new_node();

	for (i = 0; i < VOIDDB_NODE_MAX_NODE_LENGTH; i++) {
		if (i < VOIDDB_NODE_MAX_NODE_LENGTH / 2) {
			voiddb_node_copy_elem_key(*new_node_l, node, i, 0);

		} else if (i == VOIDDB_NODE_MAX_NODE_LENGTH / 2 &&
			   voiddb_node_elem_get_val_len(
				   voiddb_node_elem(node, i)) == 0) {
			voiddb_node_copy_elem(*new_node_l, node, i, 0);

			*promoted = voiddb_node_key(node, i);

			shift -= 1;

		} else if (i == VOIDDB_NODE_MAX_NODE_LENGTH / 2) {
			*promoted = voiddb_node_key(node, i - 1);

			goto fall;

		} else {
fall:
			voiddb_node_copy_elem_key(*new_node_r, node, i, shift);
		}
	}

	voiddb_node_copy_elem(*new_node_r, node, i, shift);

	voiddb_node_set_length(*new_node_l, VOIDDB_NODE_MAX_NODE_LENGTH / 2);

	voiddb_node_set_length(*new_node_r,
			       VOIDDB_NODE_MAX_NODE_LENGTH + shift);

	return;
}

void voiddb_node_insert(VOIDDB_slice node, int64_t index, int64_t pointer_l,
			int64_t pointer_r, int64_t length, VOIDDB_slice key,
			VOIDDB_slice metadata,
			// out
			VOIDDB_slice *new_node_l, VOIDDB_slice *new_node_r,
			VOIDDB_slice *promoted)
{
	int i;

	VOIDDB_slice new_node = voiddb_node_new_node();

	for (i = 0; i < voiddb_node_length(node); i++) {
		if (i < index) {
			voiddb_node_copy_elem_key(new_node, node, i, 0);

		} else {
			voiddb_node_copy_elem_key(new_node, node, i, 1);
		}
	}

	voiddb_node_copy_elem(new_node, node, i, 1);

	voiddb_node_set_key(new_node, index, key);

	voiddb_node_set_value_or_child(new_node, index, pointer_l, length,
				       metadata);

	if (pointer_r > 0) {
		voiddb_node_set_value_or_child(new_node, index + 1, pointer_r,
					       length, metadata);
	}

	if (voiddb_node_length(node) + 1 == VOIDDB_NODE_MAX_NODE_LENGTH) {
		voiddb_node_split(new_node, new_node_l, new_node_r, promoted);

		free(new_node.array);

		return;
	}

	voiddb_node_set_length(new_node, voiddb_node_length(node) + 1);

	*new_node_l = new_node;

	return;
}
