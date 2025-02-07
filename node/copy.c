#include "copy.h"

void voiddb_node_copy_elem(VOIDDB_slice node1, VOIDDB_slice node0,
			   int64_t index, int64_t shift)
{
	memcpy(voiddb_node_elem(node1, index + shift).array,
	       voiddb_node_elem(node0, index).array, VOIDDB_LINE_SIZE);

	return;
}

void voiddb_node_copy_key(VOIDDB_slice node1, VOIDDB_slice node0, int64_t index,
			  int64_t shift)
{
	memcpy(voiddb_node_key_(node1, index + shift).array,
	       voiddb_node_key_(node0, index).array,
	       VOIDDB_NODE_MAX_KEY_LENGTH);

	return;
}

void voiddb_node_copy_elem_key(VOIDDB_slice node1, VOIDDB_slice node0,
			       int64_t index, int64_t shift)
{
	voiddb_node_copy_elem(node1, node0, index, shift);

	voiddb_node_copy_key(node1, node0, index, shift);

	return;
}
