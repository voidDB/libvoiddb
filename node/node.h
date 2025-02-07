#include <stdlib.h>

#include "../include/common.h"

#include "elem.c"
#include "key.c"
#include "meta.h"

VOIDDB_slice voiddb_node_new_node();

bool voiddb_node_is_node(VOIDDB_slice node);

int64_t voiddb_node_length(VOIDDB_slice node);

int voiddb_node_set_length(VOIDDB_slice node, int64_t length);

void voiddb_node_value_or_child(VOIDDB_slice node, int64_t index,
				// out
				int64_t *pointer, int64_t *length);

int voiddb_node_set_value_or_child(VOIDDB_slice node, int64_t index,
				   int64_t pointer, int64_t length,
				   VOIDDB_slice metadata);

VOIDDB_slice voiddb_node_key(VOIDDB_slice node, int64_t index);

int voiddb_node_set_key(VOIDDB_slice node, int64_t index, VOIDDB_slice key);
