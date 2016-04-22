//
//  Pieces.h
//  Animal
//
//  Created by yang_xiong on 16/4/9.
//
//

#ifndef Pieces_h
#define Pieces_h
#include "cocos2d.h"
#include <iostream>
#include "Move.h"

USING_NS_CC;
class Pieces : public Node{
public:
    enum TypePiece {NIL,RAT,CAT,WOLF,DOG,LEOPARD,TIGER,LION,ELEPHANT};
private:
    PointXY pos; //列，行
    int player;
    TypePiece type;
    float chessPower;
	bool eaten;
protected:
    Sprite* m_sprite;
    
public:
    CREATE_FUNC(Pieces);
    virtual bool init();
    void bindSprite(Sprite* sprite);
    void setProperty(PointXY p, int play, TypePiece t);
    TypePiece getType();
    PointXY getPositionBlock();
    void setPositionBlock(PointXY p, bool show = true);
    Sprite* getSprite();
    int getPlayer();
	void setEatenValue( bool val );
    void highlight();
    void recover();
    
	bool isEaten();
    int getDistanceToEnemyBase();
    float getDistanceValue(int dis);
    void setChessPowerValue();
    float getChessPowerValue();
    
};
#endif /* Pieces_h */
