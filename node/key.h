#include <string.h>

#include "../include/common.h"
#include "../include/node.h"

VOIDDB_slice voiddb_node_key_(VOIDDB_slice node, int64_t index);

VOIDDB_slice voiddb_node_key_get(VOIDDB_slice key, int64_t length);

int64_t voiddb_node_key_set(VOIDDB_slice key, VOIDDB_slice source);
