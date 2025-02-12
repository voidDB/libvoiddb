#include "medium.h"

VOIDDB_slice medium_meta()
{
	char *metadata = "voidTestMetadata";

	return (VOIDDB_slice){ metadata, strlen(metadata) };
}

int64_t medium_save(VOIDDB_cursor_medium *medium, VOIDDB_slice data)
{
	VOIDDB_slice ether = *(VOIDDB_slice *)(medium->ether);

	int64_t pointer = ether.length;

	int64_t new_length = ether.length + data.length;

	if (new_length % VOIDDB_PAGE_SIZE > 0) {
		new_length = new_length + VOIDDB_PAGE_SIZE -
			     data.length % VOIDDB_PAGE_SIZE;
	}

	if (data.length > 0) {
		memcpy(ether.array + ether.length, data.array, data.length);
	}

	((VOIDDB_slice *)(medium->ether))->length = new_length;

	return pointer;
}

VOIDDB_slice medium_load(VOIDDB_cursor_medium *medium, int64_t offset,
			 int64_t length)
{
	VOIDDB_slice ether = *(VOIDDB_slice *)(medium->ether);

	return (VOIDDB_slice){ ether.array + offset, length };
}

void medium_free(VOIDDB_cursor_medium *, int64_t, int64_t)
{
	return;
}

VOIDDB_cursor_medium *new_medium()
{
	VOIDDB_cursor_medium *medium = malloc(sizeof(VOIDDB_cursor_medium));

	medium->meta = &medium_meta;
	medium->save = &medium_save;
	medium->load = &medium_load;
	medium->free = &medium_free;

	medium->ether = malloc(sizeof(VOIDDB_slice));

	*(VOIDDB_slice *)(medium->ether) = (VOIDDB_slice){ malloc(1048576), 0 };

	return medium;
}
