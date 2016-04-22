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
	if (t == NIL)
		eaten = true;
	else
		eaten = false;
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
void Pieces::setEatenValue( bool val)
{
	eaten = val;
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
void Pieces::setPositionBlock(PointXY p, bool show /*= true*/){
    pos = p;
	if (show) {
		setPosition((p.x + 1) * 80.0 + 40, (7 - p.y) * 70.0 + 35);
	}
}


Sprite* Pieces::getSprite(){
    return m_sprite;
}

bool Pieces::isEaten()
{
	return eaten;
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

	float ret = 0.0;

    /*
>>>>>>> origin/master
    switch (dis) {
        case 11:
            ret =  30.0;
            break;
        case 10:
            ret =  150.0;
            break;
        case 9:
            ret =  180.0;
            break;
        case 8:
            ret =  220.0;
            break;
        case 7:
            ret =  200;
            break;
        case 6:
            ret =  200.0;
            break;
        case 5:
            ret =  300.0;
            break;
        case 4:
            ret =  400.0;
            break;
        case 3:
            ret =  600.0;
            break;
        case 2:
            ret =  800.0;
            break;
        case 1:
            ret =  1000.0;
            break;
        default:
            ret =  10000.0;
            break;
    }
	ret += getChessPowerValue() * 0.15 / 11 * (11-getDistanceToEnemyBase());
	*/
    return distanceValues[dis];

}
void Pieces::setChessPowerValue(Gene gene){
    /*
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
            chessPower = 1200;
            break;
        default:
            chessPower = 0;
            break;
    }
     */
    switch (type) {//NIL,RAT,CAT,WOLF,DOG,LEOPARD,TIGER,LION,ELEPHANT
        case RAT:
            chessPower = gene.getGene().at(0);
            break;
        case CAT:
            chessPower = gene.getGene().at(1);
            break;
        case WOLF:
            chessPower = gene.getGene().at(2);
            break;
        case DOG:
            chessPower = gene.getGene().at(3);
            break;
        case LEOPARD:
            chessPower = gene.getGene().at(4);
            break;
        case TIGER:
            chessPower = gene.getGene().at(5);
            break;
        case LION:
            chessPower = gene.getGene().at(6);
            break;
        case ELEPHANT:
            chessPower = gene.getGene().at(7);
            break;
        default:
            chessPower = 0;
            break;
    }

    
}
void Pieces::setDistanceValye(Gene gene){
    for(int i = 8 ; i< 20 ;i++){
        distanceValues.push_back(gene.getGene().at(i));
    }
}

float Pieces::getChessPowerValue(){
	if (isEaten())
		return 0;
	return chessPower;
}

void Pieces::setGene(Gene & gene)
{
	setChessPowerValue(gene);  //index 0-7 represent chess value 
	setDistanceValye(gene); //index 8-19 represent distance value from  dis =0 to dis = 11
	threatenFraction = gene.getGene().at(20);
}

