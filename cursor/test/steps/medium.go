package steps

/*
#include "medium.h"
*/
import "C"

type Medium struct {
	cMedium *C.VOIDDB_cursor_medium
}

func newMedium() Medium {
	return Medium{C.new_medium()}
}
