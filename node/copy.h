#include <string.h>

#include "../include/common.h"

#include "elem.h"
#include "key.h"

void voiddb_node_copy_elem(VOIDDB_slice node1, VOIDDB_slice node0,
			   int64_t index, int64_t shift);

void voiddb_node_copy_key(VOIDDB_slice node1, VOIDDB_slice node0, int64_t index,
			  int64_t shift);

void voiddb_node_copy_elem_key(VOIDDB_slice node1, VOIDDB_slice node0,
			       int64_t index, int64_t shift);
