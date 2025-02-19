package steps

/*
#include "../../../cursor/include.h"
*/
import "C"

import (
	"context"
	"fmt"

	"github.com/cucumber/godog"
	"github.com/stretchr/testify/assert"
)

func AddStepGet(sc *godog.ScenarioContext) {
	sc.Then(`^I should get "([^"]*)", "([^"]*)" using "([^"]*)"$`, get)

	return
}

func get(ctx0 context.Context, key, valueExpect, name string) (
	ctx context.Context, e error,
) {
	ctx = ctx0

	var (
		cursor = ctx.Value(ctxKeyCursor{name}).(*C.VOIDDB_cursor)

		keySlice = []byte(key)

		valueActual = new(C.VOIDDB_slice)

		cError C.int = C.voiddb_cursor_get(cursor,
			C.VOIDDB_slice{
				C.CBytes(keySlice),
				C.int64_t(len(keySlice)),
				nil,
			},
			valueActual,
		)
	)

	if cError != 0 {
		e = fmt.Errorf("%d", cError)

		return
	}

	assert.Equal(
		godog.T(ctx),
		[]byte(valueExpect),
		C.GoBytes(
			valueActual.array,
			C.int(valueActual.length),
		),
	)

	return
}
