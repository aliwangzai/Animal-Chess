//
//  Player.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/11.
//
//
#include "Player.h"




vector<Move> Player::genAllMoves( Board & board)
{
	vector<Move> ret;
	for (int type = Pieces::TypePiece::ELEPHANT; type > Pieces::TypePiece::NIL; type--) {
		auto onePieceMove = genAMove(board, board.allPieces[type*2 + board.currentPlayer]);
		for (auto a : onePieceMove) {
			if (ret.size() < 5)
				ret.push_back(a);
			else
				ret.push_back(a);
			//	break;
		}
	}
	return ret;
}

float Player::eval( Board& board){
    //Pieces::getDistanceToEnemyBase() 获取棋子离敌方base的距离
    //pieces::getChessPower() 获取子力

	float sumPower[2] = { 0,0 };
	float sumDistanceValue[2] = { 0,0 };
	float threatento[2] = { 0,0 };
	float eval = 0;
	
	// for each pieces
	for (auto &ps = board.allPieces.begin() + 2; ps < board.allPieces.end(); ps++) {
		auto piece = *ps;
		int player = piece->getPlayer();
		if (!board.hasPiece(piece->getType(),player))
			continue;
		// pieces power
		if (board.getTerrain(piece->getPositionBlock()) == Board::TRAP)
			sumPower[player] += 0;
		else if (piece->getType() == Pieces::RAT && board.hasPiece(Pieces::ELEPHANT, !player))
			sumPower[player] += 500;
		else
			sumPower[player] += piece->getChessPowerValue();
		// Distance
		sumPower[player] += piece->getDistanceValue(piece->getDistanceToEnemyBase());
		// threaten
		auto possibleMoves = genAMove(board, piece);
		for (auto mv : possibleMoves) {
			auto toPieces = board.getPiece(mv.to);
			if (toPieces->getType() != Pieces::NIL) 
				sumPower[player] += toPieces->getChessPowerValue()/2.0;
		}
	}
	board.fcoutBoard();
	eval = sumPower[0] - sumPower[1];
	return -eval;
	/*
	2016-04-20: commented by lwl, rewrite as above
	this takes 7*9 = 63 times loop, we can do evaluation in 16 times loop

	
    float sumPower0=0, sumPower1=0;
    float sumDistanceValue0=0, sumDistanceValue1=0;
    float threatenTo0=0, threatenTo1=0;
    float evalValue = 0;

    for(int i= 0 ;i < 9 ;i++){
        for(int j = 0; j<7 ;j++){
            Pieces* tempPiece = board.getPiece(PointXY(i,j));
            if(tempPiece->getType()!=Pieces::TypePiece::NIL && !tempPiece->isEaten()){//循环扫到一个棋子
                if(tempPiece->getPlayer()==0){//扫到的是玩家0的棋子
                    //计算子力
                    if(tempPiece->getType() == Pieces::TypePiece::RAT && board.hasPiece(Pieces::TypePiece::ELEPHANT, 1))

                        sumPower0 = sumPower0 + 500;
                    else
                        sumPower0 = sumPower0 + tempPiece->getChessPowerValue();
                    //计算距离价值
                    sumDistanceValue0 = sumDistanceValue0 + tempPiece->getDistanceValue(tempPiece->getDistanceToEnemyBase());
                    //计算威胁价值
                    vector<Move> possibleMoves = genAMove(board,tempPiece);//可以到达则我方棋子比对方大
                    for(int i = 0; i < possibleMoves.size() ;i++){
                        Pieces* toPiece = board.getPiece(possibleMoves[i].to);
                        if(toPiece->getType()!=Pieces::TypePiece::NIL ){
                            //我放比对方大，增加对方威胁
                            threatenTo1 = threatenTo1 + toPiece->getChessPowerValue()/2;//取棋子1/2的power值作为对对方的威胁
                        }
                    }
                }
                else{//扫到的为玩家1的棋子
                    //计算子力

                    if(tempPiece->getType() == Pieces::TypePiece::RAT && board.hasPiece (Pieces::TypePiece::ELEPHANT,0))
                        sumPower1 = sumPower1 + 500;
                    else
                        sumPower1 = sumPower1 + tempPiece->getChessPowerValue();
                    //计算距离价值
                    sumDistanceValue1 = sumDistanceValue1 + tempPiece->getDistanceValue(tempPiece->getDistanceToEnemyBase());
                    //计算威胁价值
                    vector<Move> possibleMoves = genAMove(board,tempPiece);
                    for(int i = 0; i < possibleMoves.size() ;i++){
                        Pieces* toPiece = board.getPiece(possibleMoves[i].to);
                        if(toPiece->getType()!=Pieces::TypePiece::NIL ){
                            //我放比对方大，增加对方威胁
                            threatenTo0 = threatenTo0 + toPiece->getChessPowerValue()/2;//取棋子1/2的power值作为对对方的威胁
                        }
                    }
                }
            }
            else{//循环扫到的格子为空格子
                //do nothing
            }
        }
    }
    evalValue =(sumPower1+sumDistanceValue1+threatenTo0) - (sumPower0 + sumDistanceValue0 + threatenTo1);
    return evalValue;
	*/
}

vector<Move> Player::genAMove( Board &board, Pieces * fromPiece){
	if (fromPiece->isEaten()) {
		return vector<Move>();
	}

    PointXY fromXY = fromPiece->getPositionBlock();
    vector<Move> potentialMoves;
    Move potentialMove;
    potentialMove.from = fromXY;
    
    if(fromPiece->getType() == Pieces::TypePiece::LION || fromPiece->getType() == Pieces::TypePiece::TIGER){
        if(board.getTerrain(PointXY (fromXY.x+1,fromXY.y))==Board::TypeTerrain::RIVER){//右边有河
            potentialMove.to = PointXY(fromXY.x+4,fromXY.y);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x-1,fromXY.y);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y+1);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y-1);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
        }
        else if(board.getTerrain(PointXY (fromXY.x-1,fromXY.y))==Board::TypeTerrain::RIVER){//左边有河
            potentialMove.to = PointXY(fromXY.x+1,fromXY.y);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x-4,fromXY.y);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y+1);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y-1);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
        }
        else if(fromXY.y == 0 && board.getTerrain(PointXY (fromXY.x,fromXY.y+1))==Board::TypeTerrain::RIVER){//下面有河
            potentialMove.to = PointXY(fromXY.x+1,fromXY.y);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x-1,fromXY.y);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y+3);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            //已经在上边缘不用考虑向上走
        }
        else if(fromXY.y == 6 && board.getTerrain(PointXY (fromXY.x,fromXY.y-1))==Board::TypeTerrain::RIVER){//上面有河
            potentialMove.to = PointXY(fromXY.x+1,fromXY.y);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x-1,fromXY.y);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y-3);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            //已经在下边缘不用考虑向下走
        }
        else if(fromXY.y == 3 && board.getTerrain(PointXY (fromXY.x,fromXY.y-1))==Board::TypeTerrain::RIVER && board.getTerrain(PointXY (fromXY.x,fromXY.y+1))==Board::TypeTerrain::RIVER){//在河之间
            potentialMove.to = PointXY(fromXY.x+1,fromXY.y);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x-1,fromXY.y);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y+3);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y-3);
            if(board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
        }
        else{//不挨着河
            potentialMove.to = PointXY(fromXY.x+1,fromXY.y);
            if(fromXY.x+1<=8 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x-1,fromXY.y);
            if(fromXY.x-1>=0 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y+1);
            if(fromXY.y+1<=6 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y-1);
            if(fromXY.y-1>=0 &&board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
        }
    }
    else{//其他动物
		//优先生成向前的move
		if (fromPiece->getPlayer()) {
			potentialMove.to = PointXY(fromXY.x - 1, fromXY.y);
			if (fromXY.x - 1 >= 0 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x + 1, fromXY.y);
			if (fromXY.x + 1 <= 8 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
		} else {
			potentialMove.to = PointXY(fromXY.x + 1, fromXY.y);
			if (fromXY.x + 1 <= 8 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x - 1, fromXY.y);
			if (fromXY.x - 1 >= 0 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
		}
			potentialMove.to = PointXY(fromXY.x, fromXY.y + 1);
			if (fromXY.y + 1 <= 6 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x, fromXY.y - 1);
			if (fromXY.y - 1 >= 0 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
		}
    return potentialMoves;


}

