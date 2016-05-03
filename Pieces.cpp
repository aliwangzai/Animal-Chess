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
	return distanceValues_Types[type][dis];
}

void Pieces::setChessPowerValue(Gene gene){
	if (type == NIL)
		chessPower = 0;
	else
		chessPower = gene.getGene()[(int)type+1];
}

void Pieces::setDistanceValye(Gene gene){
	for( int type = 1; type <= 8; type++){
		distanceValues_Types[type].push_back(10000);
		distanceValues_Types[type].push_back(1000);
		int s = 10 * type;
		for(int i = s; i < s + 10 ;i++)
			distanceValues_Types[type].push_back( gene.getGene().at(i) );
	}
}

float Pieces::getChessPowerValue(){
	if (isEaten())
		return 0;
	return chessPower;
}

void Pieces::setGene(Gene & gene)
{
    riverBounus = gene.getGene().at(0);
	threatenFraction = gene.getGene().at(1);
	setChessPowerValue(gene);  //index 2-9
	setDistanceValye(gene); //index 10-90
}

Pieces::Pieces()
{
	for (int i = 0; i <= 8; i++)
		distanceValues_Types.push_back(vector<float>());
}

