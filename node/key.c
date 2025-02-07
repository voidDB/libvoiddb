#include "key.h"

VOIDDB_slice voiddb_node_key_(VOIDDB_slice node, int64_t index)
{
	return voiddb_common_field(node,
				   VOIDDB_NODE_MAX_KEY_LENGTH * (index + 1),
				   VOIDDB_NODE_MAX_KEY_LENGTH);
}

VOIDDB_slice voiddb_node_key_get(VOIDDB_slice key, int64_t length)
{
	return voiddb_common_field(key, 0, length);
}

int64_t voiddb_node_key_set(VOIDDB_slice key, VOIDDB_slice source)
{
	int64_t length = source.length;

	if (length > VOIDDB_NODE_MAX_KEY_LENGTH) {
		length = VOIDDB_NODE_MAX_KEY_LENGTH;
	}

	memcpy(key.array, source.array, length);

	return length;
}
