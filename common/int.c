#include "include.h"

uint64_t voiddb_common_get_uint64(VOIDDB_slice slice)
{
	uint8_t *array = (uint8_t *)slice.array;

	return (uint64_t)array[0] << 56 | (uint64_t)array[1] << 48 |
	       (uint64_t)array[2] << 40 | (uint64_t)array[3] << 32 |
	       (uint64_t)array[4] << 24 | (uint64_t)array[5] << 16 |
	       (uint64_t)array[6] << 8 | (uint64_t)array[7];
}

uint32_t voiddb_common_get_uint32(VOIDDB_slice slice)
{
	uint8_t *array = (uint8_t *)slice.array;

	return (uint32_t)array[0] << 24 | (uint32_t)array[1] << 16 |
	       (uint32_t)array[2] << 8 | (uint32_t)array[3];
}

int64_t voiddb_common_get_int(VOIDDB_slice slice)
{
	switch (slice.length) {
	case VOIDDB_WORD_SIZE:
		uint64_t uint64 = voiddb_common_get_uint64(slice);

		if (uint64 > INT64_MAX) {
			goto bad;
		}

		return (int64_t)uint64;

	case VOIDDB_HALF_SIZE:
		uint32_t uint32 = voiddb_common_get_uint32(slice);

		return (int64_t)uint32;
	}

bad:
	return -1;
}

int voiddb_common_put_uint64(VOIDDB_slice slice, uint64_t u)
{
	if (slice.length != VOIDDB_WORD_SIZE) {
		return -1;
	}

	uint8_t *array = (uint8_t *)slice.array;

	array[0] = (uint8_t)(u >> 56);
	array[1] = (uint8_t)(u >> 48);
	array[2] = (uint8_t)(u >> 40);
	array[3] = (uint8_t)(u >> 32);
	array[4] = (uint8_t)(u >> 24);
	array[5] = (uint8_t)(u >> 16);
	array[6] = (uint8_t)(u >> 8);
	array[7] = (uint8_t)u;

	return 0;
}

int voiddb_common_put_uint32(VOIDDB_slice slice, uint32_t u)
{
	if (slice.length != VOIDDB_HALF_SIZE) {
		return -1;
	}

	uint8_t *array = (uint8_t *)slice.array;

	array[0] = (uint8_t)(u >> 24);
	array[1] = (uint8_t)(u >> 16);
	array[2] = (uint8_t)(u >> 8);
	array[3] = (uint8_t)u;

	return 0;
}

int voiddb_common_put_int(VOIDDB_slice slice, int64_t i)
{
	if (i < 0) {
		goto bad;
	}

	switch (slice.length) {
	case VOIDDB_WORD_SIZE:
		return voiddb_common_put_uint64(slice, (uint64_t)i);

	case VOIDDB_HALF_SIZE:
		if (i > UINT32_MAX) {
			goto bad;
		}

		return voiddb_common_put_uint32(slice, (uint32_t)i);
	}

bad:
	return -1;
}
