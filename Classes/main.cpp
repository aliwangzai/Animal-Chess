#include "Board.h"
#include "Player.h"
#include "AI_Min_Max.h"

#include "Piece.cpp"
#include "AI_Min_Max.cpp"


int main(){
	Board b;
	Player p1;
	p1.genMove(b);

	Piece pc1;
	pc1.getType();
	pc1.getPosition();
	pc1.getPlayer();
	return 0;
}