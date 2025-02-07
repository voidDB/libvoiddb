#pragma once

#include "common.h"

typedef struct VOIDDB_cursor VOIDDB_cursor;

typedef struct VOIDDB_cursor_medium {
	VOIDDB_slice (*meta)();
	int64_t (*save)(VOIDDB_slice);
	VOIDDB_slice (*load)(int64_t, int64_t);
	void (*free)(int64_t, int64_t);
} VOIDDB_cursor_medium;
