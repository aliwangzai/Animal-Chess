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

void Pieces::setPositionBlock(PointXY p, bool show /*= true*/){
    pos = p;
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

float Pieces::getDistanceValue(int dis, int _player){
	return distanceValues_Types[_player][type][dis];
}

void Pieces::setChessPowerValue(Gene gene, int _player){
	if (type == NIL)
		chessPower[_player] = 0;
	else
		chessPower[_player] = gene.getGene()[(int)type+1];
}

void Pieces::setDistanceValye(Gene gene, int _player){
	for( int type = 1; type <= 8; type++){
		distanceValues_Types[_player][type].push_back(10000);
		distanceValues_Types[_player][type].push_back(1000);
		int s = 10 * type;
		for(int i = s; i < s + 10 ;i++)
			distanceValues_Types[_player][type].push_back( gene.getGene().at(i) );
	}
}

float Pieces::getChessPowerValue(int _player){
	if (isEaten())
		return 0;
	return chessPower[_player];
}

void Pieces::setGene(Gene & gene, int _player)
{
    riverBounus[_player] = gene.getGene().at(0);
	threatenFraction[_player] = gene.getGene().at(1);
	setChessPowerValue(gene, _player);  //index 2-9
	setDistanceValye(gene, _player); //index 10-90
}

Pieces::Pieces()
{
	for (int i = 0; i <= 8; i++) {
		distanceValues_Types[0].push_back(vector<float>());
		distanceValues_Types[1].push_back(vector<float>());
	}
}

