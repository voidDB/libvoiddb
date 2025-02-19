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

func AddStepGetNext(sc *godog.ScenarioContext) {
	sc.Then(`^I should get "([^"]*)", "([^"]*)" next using "([^"]*)"$`, getNext)

	sc.Then(`^getting next using "([^"]*)" should not find$`, getNextNotFound)

	return
}

func getNext(ctx0 context.Context, keyExpect, valueExpect, name string) (
	ctx context.Context, e error,
) {
	ctx = ctx0

	var (
		cursor = ctx.Value(ctxKeyCursor{name}).(*C.VOIDDB_cursor)

		keyActual   = new(C.VOIDDB_slice)
		valueActual = new(C.VOIDDB_slice)

		cError C.int = C.voiddb_cursor_get_next(cursor, keyActual, valueActual)
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

func getNextNotFound(ctx0 context.Context, name string) (
	ctx context.Context, e error,
) {
	ctx = ctx0

	var (
		cursor = ctx.Value(ctxKeyCursor{name}).(*C.VOIDDB_cursor)

		cError C.int = C.voiddb_cursor_get_next(cursor,
			new(C.VOIDDB_slice),
			new(C.VOIDDB_slice),
		)
	)

	assert.Equal(
		godog.T(ctx),
		cError,
		C.int(C.VOIDDB_ERROR_NOT_FOUND),
	)

	return
}
