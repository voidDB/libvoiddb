package steps

/*
#cgo CFLAGS: -g -Wall
#cgo LDFLAGS: -L../lib -lvoiddb

#include "../../../cursor/include.h"
#include "../../../node/include.h"

#include "medium.h"
*/
import "C"

import (
	"context"

	"github.com/cucumber/godog"
)

func AddStepNewTree(sc *godog.ScenarioContext) {
	sc.Given(`^there is a new tree "([^"]*)"$`, newTree)

	return
}

func newTree(ctx0 context.Context, name string) (ctx context.Context, e error) {
	ctx = ctx0

	var (
		medium Medium = newMedium()

		offset C.int64_t = C.medium_save(medium.cMedium,
			C.voiddb_node_new_node(),
		)
	)

	ctx = context.WithValue(ctx, ctxKeyTree{name},
		root{medium, offset},
	)

	return
}

type ctxKeyTree struct {
	Name string
}

type root struct {
	medium Medium
	offset C.int64_t
}
