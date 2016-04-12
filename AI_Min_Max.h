#pragma once


#include "Player.h"

class AI_Min_Max : public Player{
	Move genMove(const Board &board);
	float eval( const Board &board);
};