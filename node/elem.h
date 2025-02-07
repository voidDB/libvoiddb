#include <string.h>

#include "../include/common.h"
#include "../include/node.h"

VOIDDB_slice voiddb_node_elem(VOIDDB_slice node, int64_t index);

VOIDDB_slice voiddb_node_elem_key_len(VOIDDB_slice elem);

int64_t voiddb_node_elem_get_key_len(VOIDDB_slice elem);

int voiddb_node_elem_set_key_len(VOIDDB_slice elem, int64_t length);

VOIDDB_slice voiddb_node_elem_val_len(VOIDDB_slice elem);

int64_t voiddb_node_elem_get_val_len(VOIDDB_slice elem);

int voiddb_node_elem_set_val_len(VOIDDB_slice elem, int64_t length);

VOIDDB_slice voiddb_node_elem_pointer(VOIDDB_slice elem);

int64_t voiddb_node_elem_get_pointer(VOIDDB_slice elem);

int voiddb_node_elem_set_pointer(VOIDDB_slice elem, int64_t length);

VOIDDB_slice voiddb_node_elem_extra_metadata(VOIDDB_slice elem);

void voiddb_node_elem_set_extra_metadata(VOIDDB_slice elem,
					 VOIDDB_slice metadata);
