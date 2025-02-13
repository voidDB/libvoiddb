package steps

/*
#include "../../../include/cursor.h"
*/
import "C"

import (
	"context"
	"fmt"

	"github.com/cucumber/godog"
)

func AddStepDel(sc *godog.ScenarioContext) {
	sc.When(`^I delete using "([^"]*)"$`, del)

	return
}

func del(ctx0 context.Context, name string) (ctx context.Context, e error) {
	ctx = ctx0

	var (
		cursor = ctx.Value(ctxKeyCursor{name}).(*C.VOIDDB_cursor)

		cError C.int = C.voiddb_cursor_del(cursor)
	)

	if cError != 0 {
		e = fmt.Errorf("%d", cError)

		return
	}

	return
}
