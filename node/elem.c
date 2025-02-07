#include "elem.h"

VOIDDB_slice voiddb_node_elem(VOIDDB_slice node, int64_t index)
{
	return voiddb_common_field(
		node,
		VOIDDB_LINE_SIZE *
			((index + 1) % (VOIDDB_NODE_MAX_NODE_LENGTH + 1)),
		VOIDDB_LINE_SIZE);
}

VOIDDB_slice voiddb_node_elem_key_len(VOIDDB_slice elem)
{
	return voiddb_common_field(elem, 0, VOIDDB_HALF_SIZE);
}

int64_t voiddb_node_elem_get_key_len(VOIDDB_slice elem)
{
	return voiddb_common_get_int(voiddb_node_elem_key_len(elem));
}

int voiddb_node_elem_set_key_len(VOIDDB_slice elem, int64_t length)
{
	return voiddb_common_put_int(voiddb_node_elem_key_len(elem), length);
}

VOIDDB_slice voiddb_node_elem_val_len(VOIDDB_slice elem)
{
	return voiddb_common_field(elem, VOIDDB_HALF_SIZE, VOIDDB_HALF_SIZE);
}

int64_t voiddb_node_elem_get_val_len(VOIDDB_slice elem)
{
	return voiddb_common_get_int(voiddb_node_elem_val_len(elem));
}

int voiddb_node_elem_set_val_len(VOIDDB_slice elem, int64_t length)
{
	return voiddb_common_put_int(voiddb_node_elem_val_len(elem), length);
}

VOIDDB_slice voiddb_node_elem_pointer(VOIDDB_slice elem)
{
	return voiddb_common_field(elem, VOIDDB_WORD_SIZE, VOIDDB_WORD_SIZE);
}

int64_t voiddb_node_elem_get_pointer(VOIDDB_slice elem)
{
	return voiddb_common_get_int(voiddb_node_elem_pointer(elem));
}

int voiddb_node_elem_set_pointer(VOIDDB_slice elem, int64_t length)
{
	return voiddb_common_put_int(voiddb_node_elem_pointer(elem), length);
}

VOIDDB_slice voiddb_node_elem_extra_metadata(VOIDDB_slice elem)
{
	return voiddb_common_field(elem, 2 * VOIDDB_WORD_SIZE,
				   6 * VOIDDB_WORD_SIZE);
}

void voiddb_node_elem_set_extra_metadata(VOIDDB_slice elem,
					 VOIDDB_slice metadata)
{
	int64_t length = metadata.length;

	VOIDDB_slice extra_metadata = voiddb_node_elem_extra_metadata(elem);

	if (length > extra_metadata.length) {
		length = extra_metadata.length;
	}

	memcpy(extra_metadata.array, metadata.array, length);

	return;
}
