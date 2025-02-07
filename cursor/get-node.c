#include "get-node.h"

int voiddb_cursor_get_node(VOIDDB_cursor_medium *medium, int64_t offset,
			   bool free,
			   // out
			   VOIDDB_slice *node)
{
	*node = medium->load(offset, VOIDDB_PAGE_SIZE);

	if (!voiddb_node_is_node(*node)) {
		return VOIDDB_ERROR_CORRUPT;
	}

	if (free) {
		medium->free(offset, VOIDDB_PAGE_SIZE);
	}

	return 0;
}
