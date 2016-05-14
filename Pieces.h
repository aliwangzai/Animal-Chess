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
#include "Gene.h"

USING_NS_CC;
using namespace std;
class Pieces : public Node{
public:
    enum TypePiece {NIL,RAT,CAT,WOLF,DOG,LEOPARD,TIGER,LION,ELEPHANT};
private:
    PointXY pos; //列，行
    int player;
    TypePiece type;
    float chessPower[2];
	bool eaten;
protected:
    Sprite* m_sprite;
    
public:
    CREATE_FUNC(Pieces);
    virtual bool init();
    void bindSprite(Sprite* sprite);
    void setProperty(PointXY p, int play, TypePiece t);
    void setPropertyFrom(Pieces *_from);
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
    
    float getDistanceValue(int dis,int _player);
    void setDistanceValye(Gene gene,int _player);
    void setChessPowerValue(Gene gene,int _player);
    float getChessPowerValue(int _player);
    void setGene(Gene &gen, int _player);

    float threatenFraction[2];
    vector<vector<float> > distanceValues_Types[2];

    float riverBounus[2];
    Pieces();
private:
    
    
};
#endif /* Pieces_h */
