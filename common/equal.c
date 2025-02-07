#include <string.h>

#include "../include/common.h"

bool voiddb_common_equal(VOIDDB_slice a, VOIDDB_slice b)
{
	if (a.length == b.length) {
		if (memcmp(a.array, b.array, a.length) == 0) {
			return true;
		}
	}

	return false;
}
