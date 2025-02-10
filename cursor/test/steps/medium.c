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

	VOIDDB_slice *new_ether = malloc(sizeof(VOIDDB_slice));

	*new_ether = (VOIDDB_slice){ malloc(new_length), new_length };

	if (ether.length > 0) {
		memcpy(new_ether->array, ether.array, ether.length);

		free(ether.array);
	}

	if (data.length > 0) {
		memcpy(new_ether->array + ether.length, data.array,
		       data.length);
	}

	free(medium->ether);

	medium->ether = new_ether;

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

	VOIDDB_slice *ether = malloc(sizeof(VOIDDB_slice));

	ether->length = 0;

	medium->ether = ether;

	return medium;
}
