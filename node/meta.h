#include <string.h>

#include "../include/common.h"

VOIDDB_slice voiddb_node_meta(VOIDDB_slice node);

bool voiddb_node_meta_is_node(VOIDDB_slice meta);

void voiddb_node_meta_set_magic(VOIDDB_slice meta);

int64_t voiddb_node_meta_get_length(VOIDDB_slice meta);

int voiddb_node_meta_set_length(VOIDDB_slice meta, int64_t length);
