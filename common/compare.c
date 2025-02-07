#include <string.h>

#include "../include/common.h"

int voiddb_common_compare(VOIDDB_slice a, VOIDDB_slice b)
{
	int result;

	if (a.length < b.length) {
		result = memcmp(a.array, b.array, a.length);

		return result ? result : -1;

	} else if (a.length > b.length) {
		result = memcmp(a.array, b.array, b.length);

		return result ? result : 1;

	} else {
		return memcmp(a.array, b.array, a.length);
	}
}
