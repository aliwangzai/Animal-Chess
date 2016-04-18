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
    setChessPowerValue();
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
float Pieces::getDistanceValue(int dis){
    switch (dis) {
        case 11:
            return 10;
            break;
        case 10:
            return 20;
            break;
        case 9:
            return 30;
            break;
        case 8:
            return 40;
            break;
        case 7:
            return 50;
            break;
        case 6:
            return 70;
            break;
        case 5:
            return 100;
            break;
        case 4:
            return 200;
            break;
        case 3:
            return 500;
            break;
        case 2:
            return 1000;
            break;
        case 1:
            return 5000;
            break;
        default:
            return 10000;
            break;
    }
    
    
}
void Pieces::setChessPowerValue(){
    switch (type) {//NIL,RAT,CAT,WOLF,DOG,LEOPARD,TIGER,LION,ELEPHANT
        case RAT:
            chessPower = 100;
            break;
        case CAT:
            chessPower = 200;
            break;
        case WOLF:
            chessPower = 300;
            break;
        case DOG:
            chessPower = 400;
            break;
        case LEOPARD:
            chessPower = 500;
            break;
        case TIGER:
            chessPower = 600;
            break;
        case LION:
            chessPower = 800;
            break;
        case ELEPHANT:
            chessPower = 1000;
            break;
        default:
            chessPower = 0;
            break;
    }
    
}
float Pieces::getChessPowerValue(){
    return chessPower;
}

