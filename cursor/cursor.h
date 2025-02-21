#pragma once

#include <stdlib.h>

#include "include.h"

#include "get.h"

#define VOIDDB_CURSOR_TOMBSTONE 1
#define VOIDDB_CURSOR_GRAVEYARD 2

#define VOIDDB_CURSOR_MAX_STACK_DEPTH 26

struct VOIDDB_cursor {
	VOIDDB_cursor_medium *medium;
	int64_t offset;
	int64_t index;
	VOIDDB_slice stack;
	VOIDDB_slice latest;
};

void voiddb_cursor_reset(VOIDDB_cursor *cursor);

void voiddb_cursor_resume(VOIDDB_cursor *cursor);

struct ancestor {
	int64_t offset;
	int64_t index;
};
