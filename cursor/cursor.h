#pragma once

#include <stdlib.h>

#include "../include/cursor.h"

#include "get.h"

#define VOIDDB_CURSOR_MAX_STACK_DEPTH 26
#define VOIDDB_CURSOR_TOMBSTONE 1

struct VOIDDB_cursor {
	VOIDDB_cursor_medium *medium;
	int64_t offset;
	int64_t index;
	VOIDDB_slice stack;
	VOIDDB_slice latest;
};

VOIDDB_cursor *voiddb_cursor_new_cursor(VOIDDB_cursor_medium *medium,
					int64_t offset);

void voiddb_cursor_free(VOIDDB_cursor *cursor);

void voiddb_cursor_reset(VOIDDB_cursor *cursor);

void voiddb_cursor_resume(VOIDDB_cursor *cursor);

struct ancestor {
	int64_t offset;
	int64_t index;
};
