#pragma once


#include "Player.h"
#include "Move.h"


class AI_Min_Max : public player{
	Move genMove(const Board &board);
};