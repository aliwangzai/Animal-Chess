#include "Move.h"

#include <iostream>

Move::Move() {
	to = from = { -1,-1 };
	eatenIndex = -1;
}

Move::Move(PointXY f, PointXY t) {
	from = f;
	to = t;
    eatenIndex = -1;
}

Move::~Move() {

}
