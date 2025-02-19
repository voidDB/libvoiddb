package steps

/*
#include "../../../cursor/include.h"
*/
import "C"

import (
	"context"
	"fmt"

	"github.com/cucumber/godog"
)

func AddStepPut(sc *godog.ScenarioContext) {
	sc.When(`^I put "([^"]*)", "([^"]*)" using "([^"]*)"$`, put)

	return
}

func put(ctx0 context.Context, key, value, name string) (
	ctx context.Context, e error,
) {
	ctx = ctx0

	var (
		cursor = ctx.Value(ctxKeyCursor{name}).(*C.VOIDDB_cursor)

		keySlice = []byte(key)

		valueSlice = []byte(value)

		cError C.int = C.voiddb_cursor_put(cursor,
			C.VOIDDB_slice{
				C.CBytes(keySlice),
				C.int64_t(len(keySlice)),
				nil,
			},
			C.VOIDDB_slice{
				C.CBytes(valueSlice),
				C.int64_t(len(valueSlice)),
				nil,
			},
		)
	)

	if cError != 0 {
		e = fmt.Errorf("%d", cError)

		return
	}

	return
}
