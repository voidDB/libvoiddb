#include <stdlib.h>

#include "elem.h"
#include "key.h"
#include "meta.h"

int voiddb_node_set_length(VOIDDB_slice node, int64_t length);

int voiddb_node_set_value_or_child(VOIDDB_slice node, int64_t index,
				   int64_t pointer, int64_t length,
				   VOIDDB_slice metadata);

int voiddb_node_set_key(VOIDDB_slice node, int64_t index, VOIDDB_slice key);
