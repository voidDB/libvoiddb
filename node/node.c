#include "node.h"

VOIDDB_slice voiddb_node_new_node()
{
	VOIDDB_slice node = { calloc(1, VOIDDB_PAGE_SIZE), VOIDDB_PAGE_SIZE };

	voiddb_node_meta_set_magic(voiddb_node_meta(node));

	return node;
}

bool voiddb_node_is_node(VOIDDB_slice node)
{
	return voiddb_node_meta_is_node(voiddb_node_meta(node));
}

int64_t voiddb_node_length(VOIDDB_slice node)
{
	return voiddb_node_meta_get_length(voiddb_node_meta(node));
}

int voiddb_node_set_length(VOIDDB_slice node, int64_t length)
{
	return voiddb_node_meta_set_length(voiddb_node_meta(node), length);
}

void voiddb_node_value_or_child(VOIDDB_slice node, int64_t index,
				// out
				int64_t *pointer, int64_t *length)
{
	VOIDDB_slice elem = voiddb_node_elem(node, index);

	*pointer = voiddb_node_elem_get_pointer(elem);

	*length = voiddb_node_elem_get_val_len(elem);

	return;
}

int voiddb_node_set_value_or_child(VOIDDB_slice node, int64_t index,
				   int64_t pointer, int64_t length,
				   VOIDDB_slice metadata)
{
	VOIDDB_slice elem = voiddb_node_elem(node, index);

	int e;

	e = voiddb_node_elem_set_pointer(elem, pointer);
	if (e != 0) {
		goto end;
	}

	e = voiddb_node_elem_set_val_len(elem, length);
	if (e != 0) {
		goto end;
	}

	voiddb_node_elem_set_extra_metadata(elem, metadata);

end:
	return e;
}

VOIDDB_slice voiddb_node_key(VOIDDB_slice node, int64_t index)
{
	return voiddb_node_key_get(
		voiddb_node_key_(node, index),
		voiddb_node_elem_get_key_len(voiddb_node_elem(node, index)));
}

int voiddb_node_set_key(VOIDDB_slice node, int64_t index, VOIDDB_slice key)
{
	return voiddb_node_elem_set_key_len(
		voiddb_node_elem(node, index),
		voiddb_node_key_set(voiddb_node_key_(node, index), key));
}
