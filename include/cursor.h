#pragma once

#include "common.h"

#define VOIDDB_CURSOR_MAX_KEY_LENGTH VOIDDB_NODE_MAX_KEY_LENGTH
#define VOIDDB_CURSOR_MAX_VALUE_LENGTH UINT32_MAX

typedef struct VOIDDB_cursor VOIDDB_cursor;

typedef struct VOIDDB_cursor_medium {
	VOIDDB_slice (*meta)();
	int64_t (*save)(struct VOIDDB_cursor_medium *, VOIDDB_slice);
	VOIDDB_slice (*load)(struct VOIDDB_cursor_medium *, int64_t, int64_t);
	void (*free)(struct VOIDDB_cursor_medium *, int64_t, int64_t);

	void *ether;
} VOIDDB_cursor_medium;

VOIDDB_cursor *voiddb_cursor_new_cursor(VOIDDB_cursor_medium *medium,
					int64_t offset);

int voiddb_cursor_put(VOIDDB_cursor *cursor, VOIDDB_slice key,
		      VOIDDB_slice value);

int voiddb_cursor_get(VOIDDB_cursor *cursor, VOIDDB_slice key,
		      VOIDDB_slice *value);
