#include <string.h>

#include "../include/common.h"

const VOIDDB_slice VOIDDB_NODE_MAGIC;

VOIDDB_slice voiddb_node_meta(VOIDDB_slice node);

VOIDDB_slice voiddb_node_meta_magic(VOIDDB_slice meta);

bool voiddb_node_meta_is_node(VOIDDB_slice meta);

void voiddb_node_meta_set_magic(VOIDDB_slice meta);

VOIDDB_slice voiddb_node_meta_length(VOIDDB_slice meta);

int64_t voiddb_node_meta_get_length(VOIDDB_slice meta);

int voiddb_node_meta_set_length(VOIDDB_slice meta, int64_t length);
