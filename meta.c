#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "common/include.h"
#include "vendor/fnv.h"

const VOIDDB_slice VOIDDB_META_MAGIC =
	(VOIDDB_slice){ "voidMETA", VOIDDB_WORD_SIZE };

const int64_t VOIDDB_VERSION = 0;

VOIDDB_slice voiddb_meta_magic(VOIDDB_slice meta)
{
	return voiddb_common_field(meta, 0, VOIDDB_WORD_SIZE);
}

void voiddb_meta_set_magic(VOIDDB_slice meta)
{
	memcpy(voiddb_meta_magic(meta).array, VOIDDB_META_MAGIC.array,
	       VOIDDB_WORD_SIZE);

	return;
}

VOIDDB_slice voiddb_meta_version(VOIDDB_slice meta)
{
	return voiddb_common_field(meta, VOIDDB_WORD_SIZE, VOIDDB_WORD_SIZE);
}

int64_t voiddb_meta_get_version(VOIDDB_slice meta)
{
	return voiddb_common_get_int(voiddb_meta_version(meta));
}

int voiddb_meta_set_version(VOIDDB_slice meta)
{
	return voiddb_common_put_int(voiddb_meta_version(meta), VOIDDB_VERSION);
}

VOIDDB_slice voiddb_meta_timestamp(VOIDDB_slice meta)
{
	return voiddb_common_field(meta, 2 * VOIDDB_WORD_SIZE,
				   VOIDDB_WORD_SIZE);
}

int voiddb_meta_set_timestamp(VOIDDB_slice meta)
{
	int e;
	struct timespec time;

	e = clock_gettime(CLOCK_REALTIME, &time);
	if (e != 0) {
		return e;
	}

	return voiddb_common_put_int(voiddb_meta_timestamp(meta),
				     (int64_t)(time.tv_sec) * 1e9 +
					     (int64_t)(time.tv_nsec));
}

VOIDDB_slice voiddb_meta_root_node_pointer(VOIDDB_slice meta)
{
	return voiddb_common_field(meta, 4 * VOIDDB_WORD_SIZE,
				   VOIDDB_WORD_SIZE);
}

int voiddb_meta_set_root_node_pointer(VOIDDB_slice meta, int64_t pointer)
{
	return voiddb_common_put_int(voiddb_meta_root_node_pointer(meta),
				     pointer);
}

VOIDDB_slice voiddb_meta_frontier_pointer(VOIDDB_slice meta)
{
	return voiddb_common_field(meta, 5 * VOIDDB_WORD_SIZE,
				   VOIDDB_WORD_SIZE);
}

int voiddb_meta_set_frontier_pointer(VOIDDB_slice meta, int64_t pointer)
{
	return voiddb_common_put_int(voiddb_meta_frontier_pointer(meta),
				     pointer);
}

VOIDDB_slice voiddb_meta_checksum(VOIDDB_slice meta)
{
	return voiddb_common_field(meta, 7 * VOIDDB_WORD_SIZE,
				   VOIDDB_WORD_SIZE);
}

uint64_t voiddb_meta_compute_checksum(VOIDDB_slice meta)
{
	VOIDDB_slice head = voiddb_common_field(meta, 0, 7 * VOIDDB_WORD_SIZE);

	VOIDDB_slice tail =
		voiddb_common_field(meta, 8 * VOIDDB_WORD_SIZE,
				    VOIDDB_PAGE_SIZE - 8 * VOIDDB_WORD_SIZE);

	return fnv_64a_buf(tail.array, tail.length,
			   fnv_64a_buf(head.array, head.length, FNV1A_64_INIT));
}

int voiddb_meta_set_checksum(VOIDDB_slice meta)
{
	return voiddb_common_put_uint64(voiddb_meta_checksum(meta),
					voiddb_meta_compute_checksum(meta));
}

bool voiddb_meta_checksum_ok(VOIDDB_slice meta)
{
	return voiddb_common_get_uint64(voiddb_meta_checksum(meta)) ==
	       voiddb_meta_compute_checksum(meta);
}

VOIDDB_slice voiddb_meta_new_meta()
{
	VOIDDB_slice meta = { calloc(1, VOIDDB_PAGE_SIZE), VOIDDB_PAGE_SIZE };

	voiddb_meta_set_magic(meta);

	voiddb_meta_set_version(meta);

	return meta;
}

VOIDDB_slice voiddb_meta_new_meta_init()
{
	VOIDDB_slice meta = voiddb_meta_new_meta();

	voiddb_meta_set_timestamp(meta);

	voiddb_meta_set_root_node_pointer(meta, 2 * VOIDDB_PAGE_SIZE);

	voiddb_meta_set_frontier_pointer(meta, 3 * VOIDDB_PAGE_SIZE);

	voiddb_meta_set_checksum(meta);

	return meta;
}

VOIDDB_slice voiddb_meta_make_copy(VOIDDB_slice meta)
{
	VOIDDB_slice copy = { calloc(1, VOIDDB_PAGE_SIZE), VOIDDB_PAGE_SIZE };

	memcpy(copy.array, meta.array, VOIDDB_PAGE_SIZE);

	return copy;
}

bool voiddb_meta_is_meta(VOIDDB_slice meta)
{
	if (!voiddb_meta_checksum_ok(meta)) {
		return false;

	} else if (!voiddb_common_equal(voiddb_meta_magic(meta),
					VOIDDB_META_MAGIC)) {
		return false;

	} else if (voiddb_meta_get_version(meta) != VOIDDB_VERSION) {
		return false;
	}

	return true;
}
