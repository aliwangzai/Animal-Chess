//
//  GameScene.h
//  Animal
//
//  Created by yang_xiong on 16/4/7.
//
//

#ifndef GameScene_h
#define GameScene_h

#include "Evolution.h"
#include <time.h>

#include "Board.h"
#include "AI_Min_Max.h"



class GameScene{
public:
    Board* board;
	AI_Min_Max *MinMax;
	int gameMode;
    
    virtual bool init();
	bool gameOverDetect();
    
    void operatePieceVsPeople(Move move);
    void operatePieceVsAI(Move move);
    virtual void onceUpdate();
    
    void firstAIPlay();
    void secondAIPlay();
    virtual void update();
    
    void startEvolutionPrcess();
    void finishEvolutionProcess();
  
	void releaseMem();

	void run();
	void competetition();

	GameScene() {
		board = NULL;
		MinMax = NULL;
	}
	~GameScene() {
		releaseMem();
	}

private:
    void gameOverProcess(int winner);
};

#endif /* GameScene_h */
