//
//  Pieces.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/9.
//
//

#include "Pieces.h"


void Pieces::setProperty(Point p, int play, TypePiece t){
     pos= p;
     player = play;
     type = t;
}

Point Pieces::getPositionBlock(){
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
void Pieces::changeDirection(){
    if(m_sprite->isFlippedX())
       m_sprite->setFlippedX(false);
    else
       m_sprite->setFlippedX(true);

}
void Pieces::setPositionBlock(Point p){
    pos = p;
}
Sprite* Pieces::getSprite(){
    return m_sprite;
}
