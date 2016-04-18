//
//  Player.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/11.
//
//
#include "Player.h"


Move Player::genMove(const Board& board){
    return {PointXY{0,0},PointXY{0,0}};
}


float Player::eval(Board& board){
    //Pieces::getDistanceToEnemyBase() 获取棋子离敌方base的距离
    //pieces::getChessPower() 获取子力
    float sumPower1=0, sumPower2=0;
    float sumDistance1Value=0, sumDistance2Value=0;
    float threatenTo1=0, threatenTo2=0;
    float evalValue = 0;
    for(int i= 0 ;i < 9 ;i++){
        for(int j = 0; j<7 ;j++){
            Pieces* tempPiece = board.getPiece(PointXY(i,j));
            if(tempPiece->getType()!=Pieces::TypePiece::NIL){//循环扫到一个棋子
                if(tempPiece->getPlayer()==0){//扫到的是玩家1的棋子
                    //计算子力
                    if(tempPiece->getType() == Pieces::TypePiece::RAT && board.hasElephant2 == true)
                        sumPower1 = sumPower1 + 500;
                    else
                        sumPower1 = sumPower1 + tempPiece->getChessPowerValue();
                    //计算距离价值
                    sumDistance1Value = sumDistance1Value + tempPiece->getDistanceValue(tempPiece->getDistanceToEnemyBase());
                    //计算威胁价值
                    vector<Move> possibleMoves = potentialMoves(board,tempPiece);//可以到达则我方棋子比对方大
                    for(int i = 0; i < possibleMoves.size() ;i++){
                        Pieces* toPiece = board.getPiece(possibleMoves[i].to);
                        if(toPiece->getType()!=Pieces::TypePiece::NIL && toPiece->getPlayer()==1){
                            //我放比对方大，增加对方威胁
                            threatenTo2 = threatenTo2 + toPiece->getChessPowerValue()/2;//取棋子1/2的power值作为对对方的威胁
                        }
                    }
                }
                else{//扫到的为玩家2的棋子
                    //计算子力
                    if(tempPiece->getType() == Pieces::TypePiece::RAT && board.hasElephant1 == true)
                        sumPower2 = sumPower2 + 500;
                    else
                        sumPower2 = sumPower2 + tempPiece->getChessPowerValue();
                    //计算距离价值
                    sumDistance2Value = sumDistance2Value + tempPiece->getDistanceValue(tempPiece->getDistanceToEnemyBase());
                    //计算威胁价值
                    vector<Move> possibleMoves = potentialMoves(board,tempPiece);
                    for(int i = 0; i < possibleMoves.size() ;i++){
                        Pieces* toPiece = board.getPiece(possibleMoves[i].to);
                        if(toPiece->getType()!=Pieces::TypePiece::NIL && toPiece->getPlayer()==0){
                            //我放比对方大，增加对方威胁
                            threatenTo1 = threatenTo1 + toPiece->getChessPowerValue()/2;//取棋子1/2的power值作为对对方的威胁
                        }
                    }
                }
            }
            else{//循环扫到的格子为空格子
                //do nothing
            }
        }
    }
    evalValue =(sumPower1+sumDistance1Value+threatenTo2)-(sumPower2+sumDistance2Value+threatenTo2);
    return evalValue;
}

vector<Move> Player::potentialMoves(Board &board, Pieces * fromPiece){
    PointXY fromXY = fromPiece->getPositionBlock();
    vector<Move> potentialMoves;
    Move potentialMove;
    potentialMove.from = fromXY;
    
    if(fromPiece->getType() == Pieces::TypePiece::LION || fromPiece->getType() == Pieces::TypePiece::TIGER){
        if(board.getTerrain(PointXY (fromXY.x+1,fromXY.y))==Board::TypeTerrain::RIVER){
            potentialMove.to = PointXY(fromXY.x+4,fromXY.y);
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
        else if(board.getTerrain(PointXY (fromXY.x-1,fromXY.y))==Board::TypeTerrain::RIVER){
            potentialMove.to = PointXY(fromXY.x+1,fromXY.y);
            if(fromXY.x+1<=8 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x-4,fromXY.y);
            if(fromXY.x-1>=0 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y+1);
            if(fromXY.y+1<=6 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y-1);
            if(fromXY.y-1>=0 &&board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
        }
        else if(fromXY.y == 0 && board.getTerrain(PointXY (fromXY.x,fromXY.y+1))==Board::TypeTerrain::RIVER){
            potentialMove.to = PointXY(fromXY.x+1,fromXY.y);
            if(fromXY.x+1<=8 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x-1,fromXY.y);
            if(fromXY.x-1>=0 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y+3);
            if(fromXY.y+1<=6 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y-1);
            if(fromXY.y-1>=0 &&board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
        }
        else if(fromXY.y == 6 && board.getTerrain(PointXY (fromXY.x,fromXY.y-1))==Board::TypeTerrain::RIVER){
            potentialMove.to = PointXY(fromXY.x+1,fromXY.y);
            if(fromXY.x+1<=8 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x-1,fromXY.y);
            if(fromXY.x-1>=0 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y+1);
            if(fromXY.y+1<=6 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y-3);
            if(fromXY.y-1>=0 &&board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
        }
        else if(fromXY.y == 3 && board.getTerrain(PointXY (fromXY.x,fromXY.y-1))==Board::TypeTerrain::RIVER && board.getTerrain(PointXY (fromXY.x,fromXY.y+1))==Board::TypeTerrain::RIVER){
            potentialMove.to = PointXY(fromXY.x+1,fromXY.y);
            if(fromXY.x+1<=8 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x-1,fromXY.y);
            if(fromXY.x-1>=0 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y+3);
            if(fromXY.y+1<=6 && board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
            potentialMove.to = PointXY(fromXY.x,fromXY.y-3);
            if(fromXY.y-1>=0 &&board.availableMove(potentialMove))
                potentialMoves.push_back(potentialMove);
        }
        else{
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
    else{
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
    return potentialMoves;


}

