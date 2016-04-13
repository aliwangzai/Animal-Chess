//
//  Pieces.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/9.
//
//

#include "Pieces.h"


void Pieces::setProperty(PointXY p, int play, TypePiece t){
    pos= p;
    player = play;
    type = t;
    setChessPower();
}

PointXY Pieces::getPositionBlock(){
    return pos;
}
Pieces::TypePiece Pieces::getType(){
    return type;
}

int Pieces::getPlayer(){
    return player;
    
}
void Pieces::bindSprite(Sprite* sprite){
    m_sprite = sprite;
    this->addChild(m_sprite);
}
bool Pieces::init(){
    return true;
}
void Pieces::recover(){
    ScaleTo* scale = ScaleTo::create(0.0001, 1.0f);
    m_sprite->runAction(scale);
}
void Pieces::highlight(){
    ScaleTo* scale = ScaleTo::create(0.0001, 1.2f);
    m_sprite->runAction(scale);
}

void Pieces::setPositionBlock(PointXY p){
    pos = p;
}
Sprite* Pieces::getSprite(){
    return m_sprite;
}
int Pieces::getDistanceToEnemyBase(){
    PointXY p = getPositionBlock();
    if(getPlayer()==0){
        return abs(8-p.x)+abs(3-p.y);
    }
    else{
        return abs(0-p.x)+abs(3-p.y);
    }
}
void Pieces::setChessPower(){
    switch (type) {//NIL,RAT,CAT,WOLF,DOG,LEOPARD,TIGER,LION,ELEPHANT
        case RAT:
            chessPower = 1;
            break;
        case CAT:
            chessPower = 2;
            break;
        case WOLF:
            chessPower = 3;
            break;
        case DOG:
            chessPower = 4;
            break;
        case LEOPARD:
            chessPower = 5;
            break;
        case TIGER:
            chessPower = 6;
            break;
        case LION:
            chessPower = 7;
            break;
        case ELEPHANT:
            chessPower = 8;
            break;
        default:
            chessPower = 0;
            break;
    }
    
}
float Pieces::getChessPower(){
    return chessPower;
}

