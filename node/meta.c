#include "meta.h"

const VOIDDB_slice VOIDDB_NODE_MAGIC =
	(VOIDDB_slice){ "voidNODE", VOIDDB_WORD_SIZE };

VOIDDB_slice voiddb_node_meta(VOIDDB_slice node)
{
	return voiddb_common_field(node, 0, VOIDDB_LINE_SIZE);
}

VOIDDB_slice voiddb_node_meta_magic(VOIDDB_slice meta)
{
	return voiddb_common_field(meta, 0, VOIDDB_WORD_SIZE);
}

bool voiddb_node_meta_is_node(VOIDDB_slice meta)
{
	return voiddb_common_equal(voiddb_node_meta_magic(meta),
				   VOIDDB_NODE_MAGIC);
}

void voiddb_node_meta_set_magic(VOIDDB_slice meta)
{
	memcpy(voiddb_node_meta_magic(meta).array, VOIDDB_NODE_MAGIC.array,
	       VOIDDB_WORD_SIZE);

	return;
}

VOIDDB_slice voiddb_node_meta_length(VOIDDB_slice meta)
{
	return voiddb_common_field(meta, VOIDDB_WORD_SIZE, VOIDDB_WORD_SIZE);
}

int64_t voiddb_node_meta_get_length(VOIDDB_slice meta)
{
	return voiddb_common_get_int(voiddb_node_meta_length(meta));
}

int voiddb_node_meta_set_length(VOIDDB_slice meta, int64_t length)
{
	return voiddb_common_put_int(voiddb_node_meta_length(meta), length);
}
