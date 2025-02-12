package steps

/*
#include "../../../include/cursor.h"
*/
import "C"

import (
	"context"

	"github.com/cucumber/godog"
)

func AddStepNewCursor(sc *godog.ScenarioContext) {
	sc.When(`^I open a new cursor "([^"]*)" at the root of "([^"]*)"$`,
		newCursor,
	)

	return
}

func newCursor(ctx0 context.Context, name, rootName string) (
	ctx context.Context, e error,
) {
	ctx = ctx0

	var (
		r root = ctx.Value(ctxKeyTree{rootName}).(root)
	)

	ctx = context.WithValue(ctx, ctxKeyCursor{name},
		C.voiddb_cursor_new_cursor(r.medium.cMedium, r.offset),
	)

	return
}

type ctxKeyCursor struct {
	Name string
}
