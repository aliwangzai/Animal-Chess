//
//  Board.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/11.
//
//
#include "Board.h"



bool Board::availableMove(Move move) {
	PointXY ptFrom = move.from;
	PointXY ptTo = move.to;

	auto pieceFrom = getPiece(ptFrom);
	auto pieceTo = getPiece(ptTo);

	Pieces::TypePiece pieceTypeFrom = pieceFrom->getType();
	Pieces::TypePiece pieceTypeTo = pieceTo->getType();
	auto terrainFrom = getTerrain(ptFrom);
	auto terrainTo = getTerrain(ptTo);

	if (pieceTypeFrom == Pieces::NIL || pieceFrom->isEaten()) {
		return false;
	}
	if (pieceTo->isEaten())
		pieceTypeTo = Pieces::NIL;

	// detect recursively move
	if (moveHistory.size() >= 8 && 
		(move == *(moveHistory.end() - 4)) &&
		(*(moveHistory.end() - 2) == *(moveHistory.end() - 6)) &&
		(*(moveHistory.end() - 4) == *(moveHistory.end() - 8))
		)
		return false;

	

	// check if two pieces are belong to same player
	if (pieceFrom->getPlayer() == pieceTo->getPlayer())
		return false;

	// set the priority to lowest if it is trapped
	if (terrainTo == Board::TRAP)
		pieceTypeTo = Pieces::NIL;



	// detect jumping over the river
	int diffx = ptFrom.x - ptTo.x;
	int diffy = ptFrom.y - ptTo.y;
	int distance = abs(diffx) + abs(diffy);
	if (distance == 1) {
		bool land2land = false;
		land2land = ((pieceTypeFrom == Pieces::RAT && pieceTypeTo == Pieces::ELEPHANT) || (pieceTypeFrom >= pieceTypeTo));
		land2land &= !(pieceTypeFrom == Pieces::ELEPHANT && pieceTypeTo == Pieces::RAT);
		land2land &= ((terrainFrom != RIVER) && (terrainTo != RIVER));
		if (pieceFrom->getPlayer())
			land2land &= (terrainTo != DEN1);
		else
			land2land &= (terrainTo != DEN0);
		if (land2land)
			return true;

		bool land2river = false;
		land2river = (terrainFrom == RIVER  || terrainTo == RIVER);
		land2river &= (pieceTypeFrom == Pieces::RAT);
		land2river &= pieceTypeTo == NIL;
		if (land2river)
			return true;

		bool river2river = false;
		river2river = (terrainFrom == RIVER && terrainTo == RIVER) && (pieceTypeFrom == Pieces::RAT && pieceTypeTo == Pieces::RAT);
		
		return river2river;
	}
	else{
		// must move in a line, not diagonal line
		if (diffx && diffy)
			return false;
		int signx = (diffx == 0) ? 0 : (diffx > 0 ? 1 : -1);
		int signy = (diffy == 0) ? 0 : (diffy > 0 ? 1 : -1);
		int cmpX = ptFrom.x - signx * 1;
		int cmpY = ptFrom.y - signy * 1;
		bool allRiverBetweenFromAndTo = getTerrain({ cmpX,cmpY }) == Board::RIVER;
		PointXY cmpPt = ptFrom;
		for (int i = 1; allRiverBetweenFromAndTo&&cmpPt != ptTo; i++) {
			cmpPt = PointXY{ ptFrom.x - i*signx,ptFrom.y - i*signy };
			allRiverBetweenFromAndTo &= (getTerrain(cmpPt) == Board::RIVER);
			auto cmpPiece = getPiece(cmpPt);
			// there if there is an animal that under river
			if (allRiverBetweenFromAndTo && cmpPiece->getType() != Pieces::NIL && !cmpPiece->isEaten()) {
				return false;
			}
		}
		if (cmpPt == ptTo) {
			if (!(pieceTypeFrom == Pieces::LION || pieceTypeFrom == Pieces::TIGER)) {
				return false;
			} else {
				return (terrainTo == Board::NIL) && (pieceTypeFrom >= pieceTypeTo);
			}
		} else {
			return false;
		}
	}
	// return priority
	return (pieceTypeFrom >= pieceTypeTo);
}

inline Pieces * Board::getPiece(PointXY pt)
{
	if (pt.x < 0 || pt.y < 0 || pt.x > 8 || pt.y > 6)
		return nul_piece;
	return boardPieces[pt.x][pt.y];
}

Pieces * Board::getPiece(Pieces::TypePiece type, int player)
{
	return allPieces[getPieceIndex(type, player)];
}


void Board::moveChess(Move& move, bool realMove /* = true */) {
	if (move.from == PointXY{ -1,-1 } && move.to == PointXY{ -1,-1 }) {
		return;
	}
	auto fromPiece = getPiece(move.from);
	auto to = move.to;
	auto from = fromPiece->getPositionBlock();
	auto toPiece = getPiece(to);
	auto toType = toPiece->getType();

	if (realMove)
		moveHistory.push_back(move);
	fromPiece->setPositionBlock(to, realMove);
	boardPieces[from.x][from.y] = nul_piece;
	boardPieces[to.x][to.y] = fromPiece;
	//eat
	if (toType != Pieces::NIL) {
		if (realMove)
			toPiece->setPositionBlock({ -2,-2 });
		toPiece->setEatenValue(true);
		nPiecesExisted[toPiece->getPlayer()]--;
		move.eatenIndex = getPieceIndex(toPiece->getType(), toPiece->getPlayer());
	}
	currentPlayer = !currentPlayer;
	
	if (realMove)
		whoWillMove = !whoWillMove;
}



int Board::getWinner()
{
	if (boardPieces[0][3]->getType() != Pieces::NIL || !nPiecesExisted[0])
		return 1;
	else if (boardPieces[8][3]->getType() != Pieces::NIL || !nPiecesExisted[1])
		return 0;
	else if (moveHistory.size() >= 200)
		return 2;
	else return -1;
}


bool Board::hasPiece(Pieces::TypePiece type, int player)
{
	auto piece = allPieces[getPieceIndex(type, player)];
	return (!piece->isEaten() && piece->getPositionBlock() != PointXY{ -1, -1 });
}

void Board::fcoutBoard()
{
	FILE *pf = fopen("board.txt", "w+");
	for (auto i = 0; i < boardPieces[0].size(); i++) {
		for (auto j = 0; j < boardPieces.size(); j++) {
			auto piece = boardPieces[j][i];
			switch (piece->getType()) {
			case Pieces::RAT:	fprintf(pf, "Rat\t"); break;
			case Pieces::CAT:	fprintf(pf, "Cat\t"); break;
			case Pieces::WOLF:	fprintf(pf, "Wol\t"); break;
			case Pieces::DOG:	fprintf(pf, "Dog\t"); break;
			case Pieces::LEOPARD:	fprintf(pf, "Leo\t"); break;
			case Pieces::TIGER:	fprintf(pf, "Tig\t"); break;
			case Pieces::LION:	fprintf(pf, "Lio\t"); break;
			case Pieces::ELEPHANT:	fprintf(pf, "Ele\t"); break;
			default: {
				switch (getTerrain({ j,i })) {
				case NIL:  fprintf(pf, "___\t"); break;
				case RIVER: fprintf(pf, "riv\t"); break;
				case DEN1:
				case DEN0: fprintf(pf, "den\t"); break;
				case TRAP: fprintf(pf, "tra\t"); break;
				default:break;
				}
			}break;
			}
		}
		fprintf(pf, "\n");
	}
	fclose(pf);
	system("cls");
	printf("\t");
	for (int i = 0; i <= 8; i++)
		printf("%d\t", i);
	printf("\n");
	for (auto i = 0; i < boardPieces[0].size(); i++) {
		printf("%d\t", i);
		for (auto j = 0; j < boardPieces.size(); j++) {
			auto piece = boardPieces[j][i];
			switch (piece->getType()) {
			case Pieces::RAT:	printf( "Rat\t"); break;
			case Pieces::CAT:	printf("Cat\t"); break;
			case Pieces::WOLF:	printf("Wol\t"); break;
			case Pieces::DOG:	printf("Dog\t"); break;
			case Pieces::LEOPARD:	printf("Leo\t"); break;
			case Pieces::TIGER:	printf("Tig\t"); break;
			case Pieces::LION:	printf("Lio\t"); break;
			case Pieces::ELEPHANT:	printf("Ele\t"); break;
			default: {
				switch (getTerrain({ j,i })) {
				case NIL:  printf("___\t"); break;
				case RIVER: printf("riv\t"); break;
				case DEN1:
				case DEN0: printf("den\t"); break;
				case TRAP: printf("tra\t"); break;
				default:break;
				}
			}break;
			}
		}
		printf( "\n");
	}
	printf("\n");
}

void Board::releaseMem()
{
	size_t size = allPieces.size();
	for (int i = 1; i < size; i++) {
		if (allPieces[i]) {
			delete allPieces[i];
			allPieces[i] = NULL;
		}
	}
	allPieces.clear();
	boardPieces.swap(vector<vector<Pieces*>>());
	moveHistory.clear();
}

Board::Board()
{
	terrain = {
		{ Board::NIL,Board::NIL,Board::TRAP,Board::DEN0,Board::TRAP,Board::NIL,Board::NIL },
		{ Board::NIL,Board::NIL,Board::NIL,Board::TRAP,Board::NIL,Board::NIL,Board::NIL },
		{ Board::NIL,Board::NIL,Board::NIL,Board::NIL,Board::NIL,Board::NIL,Board::NIL },
		{ Board::NIL,Board::RIVER,Board::RIVER,Board::NIL,Board::RIVER,Board::RIVER,Board::NIL },
		{ Board::NIL,Board::RIVER,Board::RIVER,Board::NIL,Board::RIVER,Board::RIVER,Board::NIL },
		{ Board::NIL,Board::RIVER,Board::RIVER,Board::NIL,Board::RIVER,Board::RIVER,Board::NIL },
		{ Board::NIL,Board::NIL,Board::NIL,Board::NIL,Board::NIL,Board::NIL,Board::NIL },
		{ Board::NIL,Board::NIL,Board::NIL,Board::TRAP,Board::NIL,Board::NIL,Board::NIL },
		{ Board::NIL,Board::NIL,Board::TRAP,Board::DEN1,Board::TRAP,Board::NIL,Board::NIL }
	};
	currentPlayer = 0;
	whoWillMove = currentPlayer;
	isThinking = false;
	moveHistory.clear();
	nul_piece = NULL;
	initPieces();
}

Board::~Board()
{
	releaseMem();
}

inline int Board::getPieceIndex(Pieces::TypePiece type, int player)
{
	return type * 2 + player;
}

void Board::initPieces() {
	releaseMem();

	Pieces* elephantPiece0 = new Pieces();
	elephantPiece0->setProperty(PointXY(2,0), 0, Pieces::ELEPHANT);

	Pieces* lionPiece0 = new Pieces();
	lionPiece0->setProperty(PointXY(0,6), 0, Pieces::LION);

	Pieces* tigerPiece0 = new Pieces();
	tigerPiece0->setProperty(PointXY(0,0), 0, Pieces::TIGER);

	Pieces* leopardPiece0 = new Pieces();
	leopardPiece0->setProperty(PointXY(2,4), 0, Pieces::LEOPARD);

	Pieces* dogPiece0 = new Pieces();
	dogPiece0->setProperty(PointXY(1,5), 0, Pieces::DOG);

	Pieces* wolfPiece0 = new Pieces();
	wolfPiece0->setProperty(PointXY(2,2), 0, Pieces::WOLF);

	Pieces* catPiece0 = new Pieces();
	catPiece0->setProperty(PointXY(1,1), 0, Pieces::CAT);

	Pieces* ratPiece0 = new Pieces();
	ratPiece0->setProperty(PointXY(2,6), 0, Pieces::RAT);

	Pieces* elephantPiece1 = new Pieces();
	elephantPiece1->setProperty(PointXY(6,6), 1, Pieces::ELEPHANT);

	Pieces* lionPiece1 = new Pieces();
	lionPiece1->setProperty(PointXY(8,0), 1, Pieces::LION);

	Pieces* tigerPiece1 = new Pieces();
	tigerPiece1->setProperty(PointXY(8,6), 1, Pieces::TIGER);

	Pieces* leopardPiece1 = new Pieces();
	leopardPiece1->setProperty(PointXY(6,2), 1, Pieces::LEOPARD);

	Pieces* dogPiece1 = new Pieces();
	dogPiece1->setProperty(PointXY(7,1), 1, Pieces::DOG);

	Pieces* wolfPiece1 = new Pieces();
	wolfPiece1->setProperty(PointXY(6,4), 1, Pieces::WOLF);

	Pieces* catPiece1 = new Pieces();
	catPiece1->setProperty(PointXY(7,5), 1, Pieces::CAT);

	Pieces* ratPiece1 = new Pieces();
	ratPiece1->setProperty(PointXY(6,0), 1, Pieces::RAT);

	nul_piece = new Pieces();
	nul_piece->setProperty({ 0,0 }, -1, Pieces::NIL);
	selected = nul_piece;
	// Must in this order!!!
	// NIL, RAT, CAT, WOLF, DOG, LEOPARD, TIGER, LION, ELEPHANTs
	allPieces.push_back(nul_piece);
	allPieces.push_back(nul_piece);
	allPieces.push_back(ratPiece0);
	allPieces.push_back(ratPiece1);
	allPieces.push_back(catPiece0);
	allPieces.push_back(catPiece1);
	allPieces.push_back(wolfPiece0);
	allPieces.push_back(wolfPiece1);
	allPieces.push_back(dogPiece0);
	allPieces.push_back(dogPiece1);
	allPieces.push_back(leopardPiece0);
	allPieces.push_back(leopardPiece1);
	allPieces.push_back(tigerPiece0);
	allPieces.push_back(tigerPiece1);
	allPieces.push_back(lionPiece0);
	allPieces.push_back(lionPiece1);
	allPieces.push_back(elephantPiece0);
	allPieces.push_back(elephantPiece1);

	nPiecesExisted[0] = nPiecesExisted[1] = 8;

	
	boardPieces = {
		{tigerPiece0,nul_piece,nul_piece, nul_piece, nul_piece, nul_piece, lionPiece0},
		{ nul_piece, catPiece0,nul_piece, nul_piece, nul_piece, dogPiece0,nul_piece},
		{elephantPiece0,nul_piece, wolfPiece0,nul_piece, leopardPiece0,nul_piece, ratPiece0},
		{ nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, nul_piece},
		{ nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, nul_piece },
		{ nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, nul_piece },
		{ratPiece1,nul_piece, leopardPiece1,nul_piece, wolfPiece1,nul_piece, elephantPiece1},
		{ nul_piece, dogPiece1,nul_piece, nul_piece, nul_piece, catPiece1,nul_piece},
		{lionPiece1,nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, tigerPiece1}
	};
	
	/*
	boardPieces = {
		{ tigerPiece0,nul_piece,nul_piece, nul_piece, nul_piece, nul_piece, lionPiece0 },
		{ nul_piece, catPiece0,nul_piece, nul_piece, nul_piece, dogPiece0,nul_piece },
		{ nul_piece,nul_piece, wolfPiece0,nul_piece, leopardPiece0,nul_piece, ratPiece0 },
		{ nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, nul_piece },
		{ nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, nul_piece },
		{ nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, nul_piece },
		{ ratPiece1,nul_piece, leopardPiece1,nul_piece, wolfPiece1,nul_piece, elephantPiece1 },
		{ nul_piece, dogPiece1,nul_piece, elephantPiece0, nul_piece, catPiece1,nul_piece },
		{ lionPiece1,nul_piece, nul_piece, nul_piece, nul_piece, nul_piece, tigerPiece1 }
	};
	*/
}


