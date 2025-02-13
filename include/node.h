#include "common.h"

#define VOIDDB_NODE_MAX_KEY_LENGTH 512
#define VOIDDB_NODE_MAX_NODE_LENGTH 7

VOIDDB_slice voiddb_node_new_node();

bool voiddb_node_is_node(VOIDDB_slice node);

int64_t voiddb_node_length(VOIDDB_slice node);

VOIDDB_slice voiddb_node_key(VOIDDB_slice node, int64_t index);

void voiddb_node_value_or_child(VOIDDB_slice node, int64_t index,
				// out
				int64_t *pointer, int64_t *length);

void voiddb_node_insert(VOIDDB_slice node, int64_t index, int64_t pointer_l,
			int64_t pointer_r, int64_t length, VOIDDB_slice key,
			VOIDDB_slice metadata,
			// out
			VOIDDB_slice *new_node_l, VOIDDB_slice *new_node_r,
			VOIDDB_slice *promoted);

void voiddb_node_search(VOIDDB_slice node, VOIDDB_slice key,
			// out
			int64_t *index, int64_t *pointer, int64_t *length);

void voiddb_node_update(VOIDDB_slice node, int64_t index, int64_t pointer,
			int64_t length, VOIDDB_slice metadata,
			// out
			VOIDDB_slice *new_node);
