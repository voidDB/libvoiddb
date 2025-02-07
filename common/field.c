#include "../include/common.h"

VOIDDB_slice voiddb_common_field(VOIDDB_slice slice, int64_t offset,
				 int64_t length)
{
	if (length > slice.length - offset) {
		length = slice.length - offset;
	}

	return (VOIDDB_slice){ slice.array + offset, length };
}
