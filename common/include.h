#pragma once

#include <stdbool.h>
#include <stdint.h>

#define VOIDDB_ERROR_CORRUPT -30796
#define VOIDDB_ERROR_NOT_FOUND -30798

#define VOIDDB_PAGE_SIZE 4096
#define VOIDDB_LINE_SIZE 64
#define VOIDDB_WORD_SIZE 8
#define VOIDDB_HALF_SIZE 4

typedef struct VOIDDB_slice {
	void *array;
	int64_t length;
	void *free_me;
} VOIDDB_slice;

int voiddb_common_compare(VOIDDB_slice a, VOIDDB_slice b);

bool voiddb_common_equal(VOIDDB_slice a, VOIDDB_slice b);

VOIDDB_slice voiddb_common_field(VOIDDB_slice slice, int64_t offset,
				 int64_t length);

int64_t voiddb_common_get_int(VOIDDB_slice slice);

int voiddb_common_put_int(VOIDDB_slice slice, int64_t i);

uint64_t voiddb_common_get_uint64(VOIDDB_slice slice);

int voiddb_common_put_uint64(VOIDDB_slice slice, uint64_t u);
