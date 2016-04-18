//
//  Board.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/11.
//
//

#include "Board.h"
#include "cocos2d.h"

using namespace cocos2d;

bool Board::availableMove(Move move) {
	PointXY ptFrom = move.from;
	PointXY ptTo = move.to;

	auto pieceFrom = getPiece(ptFrom);
	auto pieceTo = getPiece(ptTo);

	Pieces::TypePiece pieceTypeFrom = pieceFrom->getType();
	Pieces::TypePiece pieceTypeTo = pieceTo->getType();
	auto terrainFrom = getTerrain(ptFrom);
	auto terrainTo = getTerrain(ptTo);

	if (pieceTypeFrom == Pieces::NIL) {
		return false;
	}

	// check if two piece are belong to one player
	if (pieceFrom->getPlayer() == pieceTo->getPlayer())
		return false;

	// detect jumping over the river
	int diffx = ptFrom.x - ptTo.x;
	int diffy = ptFrom.y - ptTo.y;
	if (abs(diffx) + abs(diffy) > 1) {
		// must move in a line, not diagonal line
		if (diffx && diffy) return false;
		int signx = (diffx == 0) ? 0 : (diffx > 0 ? 1 : -1);
		int signy = (diffy == 0) ? 0 : (diffy > 0 ? 1 : -1);
		int cmpX = ptFrom.x - signx*1;
		int cmpY = ptFrom.y - signy*1;
		bool allRiverBetweenFromAndTo = getTerrain({ cmpX,cmpY }) == Board::RIVER;
		PointXY cmpPt = ptFrom;
		for (int i = 1; allRiverBetweenFromAndTo&&cmpPt != ptTo; i++) {
			cmpPt = PointXY{ ptFrom.x - i*signx,ptFrom.y - i*signy };
			allRiverBetweenFromAndTo &= (getTerrain(cmpPt) == Board::RIVER);
			auto cmpPiece = getPiece(cmpPt);
			// there if there is an animal that under river
			if (allRiverBetweenFromAndTo && cmpPiece->getType() != Pieces::NIL) {
				return false;
			}
		}
		if (cmpPt==ptTo) {
			if (!(pieceTypeFrom == Pieces::LION || pieceTypeFrom == Pieces::TIGER)) {
				return false;
			} else {
				return (pieceTypeFrom >= pieceTypeTo);
			}
		} else {
			return false;
		}
	}

	// detect if moving into den
	if (terrainTo == Board::DEN0) {
		return (currentPlayer != 0);
	}
	if (terrainTo == Board::DEN1) {
		return (currentPlayer != 1);
	}

	// check if the moving distance is 1
	if (abs(ptTo.x - ptFrom.x) + abs(ptTo.y - ptFrom.y) != 1) {
		return false;
	}

	// check the river and land
	if ((terrainTo == Board::RIVER && terrainFrom == Board::NIL) ||
		(terrainTo == Board::NIL && terrainFrom == Board::RIVER)) {
		if (pieceTypeTo != Pieces::NIL) {
			return false;
		} else {
			if (pieceFrom->getType() == Pieces::RAT)
				return true;
			else
				return false;
		}
	}

	// set the priority to lowest if it is trapped
	if (terrainTo == Board::TRAP) {
		pieceTypeTo = Pieces::NIL;
	}

	// check mouse and elephant
    if (pieceTypeFrom == Pieces::RAT && pieceTypeTo == Pieces::ELEPHANT){
        //if(pieceFrom->getPlayer()==0)
            //hasElephant2 = false;
        //if(pieceFrom->getPlayer()==1)
            //hasElephant1 = false;
		return true;
    }
	if (pieceTypeFrom == Pieces::ELEPHANT && pieceTypeTo == Pieces::RAT)
		return false;

	// return priority
	return (pieceTypeFrom >= pieceTypeTo);
}

Pieces * Board::getPiece(PointXY pt)
{
	return boardPieces[pt.x][pt.y];
}


void Board::moveChess(Move move) {

	auto fromPiece = getPiece(move.from);
	auto to = move.to;
	PointXY from = fromPiece->getPositionBlock();
	auto toPiece = getPiece(to);
	fromPiece->setPositionBlock(to);
	fromPiece->setPosition((to.x + 1) * 80 + 40, (7 - to.y) * 70 + 35);
	boardPieces[from.x][from.y] = nul_piece;
	boardPieces[to.x][to.y] = fromPiece;
	//eat
	if (toPiece->getType() != Pieces::NIL) {
		toPiece->removeFromParent();
	}
    currentPlayer = !currentPlayer;
	selected->recover();
	selected = nul_piece;
}

int Board::getWinner()
{
	if (boardPieces[0][3]->getType() != Pieces::NIL)
		return 1;
	else if (boardPieces[8][3]->getType() != Pieces::NIL)
		return 0;
	else return -1;
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
}

Board::~Board()
{
	if (nul_piece) {
		delete nul_piece;
		nul_piece = NULL;
	}
}

void Board::initPieces(TMXTiledMap* map) {
	TMXObjectGroup* objgroup = map->getObjectGroup("Animals");

	float x, y;
	Sprite* elephantSprite = Sprite::create("elephant.png");
	Sprite* lionSprite0 = Sprite::create("lion.png");
	Sprite* tigerSprite0 = Sprite::create("tiger.png");
	Sprite* leopardSprite0 = Sprite::create("leopard.png");
	Sprite* dogSprite0 = Sprite::create("dog.png");
	Sprite* wolfSprite0 = Sprite::create("wolf.png");
	Sprite* catSprite0 = Sprite::create("cat.png");
	Sprite* ratSprite0 = Sprite::create("rat.png");

	Sprite* elephantSprite1 = Sprite::create("elephant.png");
	Sprite* lionSprite1 = Sprite::create("lion.png");
	Sprite* tigerSprite1 = Sprite::create("tiger.png");
	Sprite* leopardSprite1 = Sprite::create("leopard.png");
	Sprite* dogSprite1 = Sprite::create("dog.png");
	Sprite* wolfSprite1 = Sprite::create("wolf.png");
	Sprite* catSprite1 = Sprite::create("cat.png");
	Sprite* ratSprite1 = Sprite::create("rat.png");

	ValueMap elephant0Pos = objgroup->getObject("elephant1");
	ValueMap lion0Pos = objgroup->getObject("lion1");
	ValueMap tiger0Pos = objgroup->getObject("tiger1");
	ValueMap leopard0Pos = objgroup->getObject("leopard1");
	ValueMap dog0Pos = objgroup->getObject("dog1");
	ValueMap wolf0Pos = objgroup->getObject("wolf1");
	ValueMap cat0Pos = objgroup->getObject("cat1");
	ValueMap rat0Pos = objgroup->getObject("rat1");

	ValueMap elephant1Pos = objgroup->getObject("elephant2");
	ValueMap lion1Pos = objgroup->getObject("lion2");
	ValueMap tiger1Pos = objgroup->getObject("tiger2");
	ValueMap leopard1Pos = objgroup->getObject("leopard2");
	ValueMap dog1Pos = objgroup->getObject("dog2");
	ValueMap wolf1Pos = objgroup->getObject("wolf2");
	ValueMap cat1Pos = objgroup->getObject("cat2");
	ValueMap rat1Pos = objgroup->getObject("rat2");

	Pieces* elephantPiece0 = Pieces::create();
	elephantPiece0->bindSprite(elephantSprite);
	x = elephant0Pos.at("x").asFloat();
	y = elephant0Pos.at("y").asFloat();
	elephantPiece0->setPosition(Point(x, y));
	elephantPiece0->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 0, Pieces::ELEPHANT);
	//std::cout<<elephant1Pos.at("x").asFloat()<<","<<elephant1Pos.at("y").asFloat();

	Pieces* lionPiece0 = Pieces::create();
	lionPiece0->bindSprite(lionSprite0);
	x = lion0Pos.at("x").asFloat();
	y = lion0Pos.at("y").asFloat();
	lionPiece0->setPosition(Point(x, y));
	lionPiece0->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 0, Pieces::LION);

	Pieces* tigerPiece0 = Pieces::create();
	tigerPiece0->bindSprite(tigerSprite0);
	x = tiger0Pos.at("x").asFloat();
	y = tiger0Pos.at("y").asFloat();
	tigerPiece0->setPosition(Point(x, y));
	tigerPiece0->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 0, Pieces::TIGER);

	Pieces* leopardPiece0 = Pieces::create();
	leopardPiece0->bindSprite(leopardSprite0);
	x = leopard0Pos.at("x").asFloat();
	y = leopard0Pos.at("y").asFloat();
	leopardPiece0->setPosition(Point(x, y));
	leopardPiece0->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 0, Pieces::LEOPARD);

	Pieces* dogPiece0 = Pieces::create();
	dogPiece0->bindSprite(dogSprite0);
	x = dog0Pos.at("x").asFloat();
	y = dog0Pos.at("y").asFloat();
	dogPiece0->setPosition(Point(x, y));
	dogPiece0->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 0, Pieces::DOG);

	Pieces* wolfPiece0 = Pieces::create();
	wolfPiece0->bindSprite(wolfSprite0);
	x = wolf0Pos.at("x").asFloat();
	y = wolf0Pos.at("y").asFloat();
	wolfPiece0->setPosition(Point(x, y));
	wolfPiece0->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 0, Pieces::WOLF);

	Pieces* catPiece0 = Pieces::create();
	catPiece0->bindSprite(catSprite0);
	x = cat0Pos.at("x").asFloat();
	y = cat0Pos.at("y").asFloat();
	catPiece0->setPosition(Point(x, y));
	catPiece0->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 0, Pieces::CAT);

	Pieces* ratPiece0 = Pieces::create();
	ratPiece0->bindSprite(ratSprite0);
	x = rat0Pos.at("x").asFloat();
	y = rat0Pos.at("y").asFloat();
	ratPiece0->setPosition(Point(x, y));
	ratPiece0->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 0, Pieces::RAT);


	Pieces* elephantPiece1 = Pieces::create();
	elephantSprite1->setFlippedX(true);
	elephantPiece1->bindSprite(elephantSprite1);
	x = elephant1Pos.at("x").asFloat();
	y = elephant1Pos.at("y").asFloat();
	elephantPiece1->setPosition(Point(x, y));
	elephantPiece1->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 1, Pieces::ELEPHANT);

	Pieces* lionPiece1 = Pieces::create();
	lionSprite1->setFlippedX(true);
	lionPiece1->bindSprite(lionSprite1);
	x = lion1Pos.at("x").asFloat();
	y = lion1Pos.at("y").asFloat();
	lionPiece1->setPosition(Point(x, y));
	lionPiece1->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 1, Pieces::LION);

	Pieces* tigerPiece1 = Pieces::create();
	tigerSprite1->setFlippedX(true);
	tigerPiece1->bindSprite(tigerSprite1);
	x = tiger1Pos.at("x").asFloat();
	y = tiger1Pos.at("y").asFloat();
	tigerPiece1->setPosition(Point(x, y));
	tigerPiece1->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 1, Pieces::TIGER);

	Pieces* leopardPiece1 = Pieces::create();
	leopardSprite1->setFlippedX(true);
	leopardPiece1->bindSprite(leopardSprite1);
	x = leopard1Pos.at("x").asFloat();
	y = leopard1Pos.at("y").asFloat();
	leopardPiece1->setPosition(Point(x, y));
	leopardPiece1->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 1, Pieces::LEOPARD);


	Pieces* dogPiece1 = Pieces::create();
	dogSprite1->setFlippedX(true);
	dogPiece1->bindSprite(dogSprite1);
	x = dog1Pos.at("x").asFloat();
	y = dog1Pos.at("y").asFloat();
	dogPiece1->setPosition(Point(x, y));
	dogPiece1->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 1, Pieces::DOG);

	Pieces* wolfPiece1 = Pieces::create();
	wolfSprite1->setFlippedX(true);
	wolfPiece1->bindSprite(wolfSprite1);
	x = wolf1Pos.at("x").asFloat();
	y = wolf1Pos.at("y").asFloat();
	wolfPiece1->setPosition(Point(x, y));
	wolfPiece1->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 1, Pieces::WOLF);

	Pieces* catPiece1 = Pieces::create();
	catSprite1->setFlippedX(true);
	catPiece1->bindSprite(catSprite1);
	x = cat1Pos.at("x").asFloat();
	y = cat1Pos.at("y").asFloat();
	catPiece1->setPosition(Point(x, y));
	catPiece1->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 1, Pieces::CAT);

	Pieces* ratPiece1 = Pieces::create();
	ratSprite1->setFlippedX(true);
	ratPiece1->bindSprite(ratSprite1);
	x = rat1Pos.at("x").asFloat();
	y = rat1Pos.at("y").asFloat();
	ratPiece1->setPosition(Point(x, y));
	ratPiece1->setProperty(PointXY((int)x / 80 - 1, 7 - (int)y / 70), 1, Pieces::RAT);


	map->addChild(elephantPiece0);
	map->addChild(lionPiece0);
	map->addChild(tigerPiece0);
	map->addChild(leopardPiece0);
	map->addChild(dogPiece0);
	map->addChild(wolfPiece0);
	map->addChild(catPiece0);
	map->addChild(ratPiece0);
	map->addChild(elephantPiece1);
	map->addChild(lionPiece1);
	map->addChild(tigerPiece1);
	map->addChild(leopardPiece1);
	map->addChild(dogPiece1);
	map->addChild(wolfPiece1);
	map->addChild(catPiece1);
	map->addChild(ratPiece1);

	allPieces.push_back(elephantPiece0);
	allPieces.push_back(lionPiece0);
	allPieces.push_back(tigerPiece0);
	allPieces.push_back(leopardPiece0);
	allPieces.push_back(dogPiece0);
	allPieces.push_back(wolfPiece0);
	allPieces.push_back(catPiece0);
	allPieces.push_back(ratPiece0);
	allPieces.push_back(elephantPiece1);
	allPieces.push_back(lionPiece1);
	allPieces.push_back(tigerPiece1);
	allPieces.push_back(leopardPiece1);
	allPieces.push_back(dogPiece1);
	allPieces.push_back(wolfPiece1);
	allPieces.push_back(catPiece1);
	allPieces.push_back(ratPiece1);
    
    hasElephant1 = true;
    hasElephant2 = true;

	nul_piece = new Pieces();
	nul_piece->setProperty({ 0,0 }, -1, Pieces::NIL);
	allPieces.push_back(nul_piece);
	selected = nul_piece;

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
}


