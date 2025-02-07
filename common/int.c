#include "../include/common.h"

int64_t voiddb_common_get_int(VOIDDB_slice slice)
{
	uint8_t *array = (uint8_t *)slice.array;

	switch (slice.length) {
	case VOIDDB_WORD_SIZE:
		uint64_t uint64 =
			(uint64_t)array[0] << 56 | (uint64_t)array[1] << 48 |
			(uint64_t)array[2] << 40 | (uint64_t)array[3] << 32 |
			(uint64_t)array[4] << 24 | (uint64_t)array[5] << 16 |
			(uint64_t)array[6] << 8 | (uint64_t)array[7];

		if (uint64 > INT64_MAX) {
			goto bad;
		}

		return (int64_t)uint64;

	case VOIDDB_HALF_SIZE:
		uint32_t uint32 = (uint32_t)array[0] << 24 |
				  (uint32_t)array[1] << 16 |
				  (uint32_t)array[2] << 8 | (uint32_t)array[3];

		return (int64_t)uint32;
	}

bad:
	return -1;
}

int voiddb_common_put_int(VOIDDB_slice slice, int64_t i)
{
	if (i < 0) {
		goto bad;
	}

	uint8_t *array = (uint8_t *)slice.array;

	switch (slice.length) {
	case VOIDDB_WORD_SIZE:
		array[0] = (uint8_t)(i >> 56);
		array[1] = (uint8_t)(i >> 48);
		array[2] = (uint8_t)(i >> 40);
		array[3] = (uint8_t)(i >> 32);
		array[4] = (uint8_t)(i >> 24);
		array[5] = (uint8_t)(i >> 16);
		array[6] = (uint8_t)(i >> 8);
		array[7] = (uint8_t)i;

	case VOIDDB_HALF_SIZE:
		if (i > UINT32_MAX) {
			goto bad;
		}

		array[0] = (uint8_t)(i >> 24);
		array[1] = (uint8_t)(i >> 16);
		array[2] = (uint8_t)(i >> 8);
		array[3] = (uint8_t)i;
	}

	return 0;

bad:
	return -1;
}
