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

func AddStepGetPrev(sc *godog.ScenarioContext) {
	sc.Then(
		`^I should get "([^"]*)", "([^"]*)" next using "([^"]*)" in reverse$`,
		getPrev,
	)

	sc.Then(`^getting next using "([^"]*)" in reverse should not find$`,
		getPrevNotFound,
	)

	return
}

func getPrev(ctx0 context.Context, keyExpect, valueExpect, name string) (
	ctx context.Context, e error,
) {
	ctx = ctx0

	var (
		cursor = ctx.Value(ctxKeyCursor{name}).(*C.VOIDDB_cursor)

		keyActual   = new(C.VOIDDB_slice)
		valueActual = new(C.VOIDDB_slice)

		cError C.int = C.voiddb_cursor_get_prev(cursor, keyActual, valueActual)
	)

	if cError != 0 {
		e = fmt.Errorf("%d", cError)

		return
	}

	assert.Equal(
		godog.T(ctx),
		[]byte(keyExpect),
		C.GoBytes(
			keyActual.array,
			C.int(keyActual.length),
		),
	)

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

func getPrevNotFound(ctx0 context.Context, name string) (
	ctx context.Context, e error,
) {
	ctx = ctx0

	var (
		cursor = ctx.Value(ctxKeyCursor{name}).(*C.VOIDDB_cursor)

		cError C.int = C.voiddb_cursor_get_prev(cursor, nil, nil)
	)

	assert.Equal(
		godog.T(ctx),
		C.int(C.VOIDDB_ERROR_NOT_FOUND),
		cError,
	)

	return
}
