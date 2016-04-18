#include "Move.h"

#include <iostream>

Move::Move() {
	to = from = { -1,-1 };
	eatinfo = NULL;
}

Move::Move(PointXY f, PointXY t) {
	from = f;
	to = t;
	eatinfo = NULL;
}

Move::~Move() {
	if (eatinfo) {
		delete eatinfo;
		eatinfo = NULL;
	}
}
