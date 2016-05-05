//
//  GameScene.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/7.
//
//

#include "GameScene.h"
#include <iostream>

extern int gameMode;

Scene* GameScene::createScene(){
    Scene* myScene = Scene::create();
    GameScene* myLayer = GameScene::create();
    myScene->addChild(myLayer);
    return myScene;
}

bool GameScene::init() {
    if (!Layer::init()) {
        return false;
    }
    TMXTiledMap* gameMap = TMXTiledMap::create("gameMap.tmx");
    this->addChild(gameMap);
    //releaseMem();
    board = new Board();
    board->initPieces(gameMap);
	MinMax = new AI_Min_Max(board);
    startEvolutionPrcess();
    //cout<<"game Mode: "<<gameMode<<endl;
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    
    listener->onTouchMoved = [](Touch* touch, Event* event) {
        return true;
    };
    
    listener->onTouchEnded = [=](Touch* touch, Event* event)->void {
        Point clickPos = Director::getInstance()->convertToGL(touch->getLocationInView());
        PointXY chosenBlock = PointXY((int)clickPos.x / 80 - 1, 7 - (int)clickPos.y / 70);
		if (board->getWinner() != -1)
			return;
        if(gameMode==0)
            operatePieceVsPeople(chosenBlock);
        if(gameMode==1 || gameMode== 2)
            operatePieceVsAI(chosenBlock);
        return;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    if(gameMode==3){
       this->scheduleOnce(schedule_selector(GameScene::startUpdate),1.0f);
    }
    return true;
}

void GameScene::startEvolutionPrcess(){
    auto E = Evolution::GetInstance();
    for(size_t a = 2; a< board->allPieces.size();a++){
        board->allPieces[a]->setGene(E->population[E->p1],0);
        board->allPieces[a]->setGene(E->population[E->p2],1);
    }
}
void GameScene::finishEvolutionProcess(){
    
    auto E = Evolution::GetInstance();
    auto &p1 = E->p1;
    auto &p2 = E->p2;
    int populationNum = E->population.size();
    auto winner = board->getWinner();
    cout << "current pair are gene " << p1 << " and gene " << p2 << endl;
    cout << "current left generation " << E->getGenerationNum() << endl;
    
    if(winner == 2){
        E->population[p2].drawGames++;
        E->population[p1].drawGames++;
    }
    else if(winner==1){
        E->population[p2].winGames++;
        E->population[p1].loseGames++;
    }
    else{
        E->population[p1].winGames++;
        E->population[p2].loseGames++;
    }
     auto g1 = E->population[p1];
     printf("[%d]'s status: %dW\t%dL\t%dD\t%f\n", p1, g1.winGames, g1.loseGames, g1.drawGames, 100.0*g1.winGames / (g1.winGames + g1.loseGames + g1.drawGames));

     if (p2 != populationNum - 1) { //not all pairs finish their game
        p2++;
     }
     else {
        p1++;
        p2 = p1 + 1;
     }
     if (p1 == populationNum - 1) {//all pair finish
        E->select();
        if (E->getGenerationNum() == 0) {
            E->storePopulationGenes();
            E->evolutionEnd = true;
            gameOverProcess(board->getWinner());//evolution end
     } else {
            p1 = 0;
            p2 = 1;
            E->storePopulationGenes();
     }
   }
    
}
void GameScene::startUpdate(float dt){
     this->scheduleUpdate();
}
void GameScene::update(float dt){
    if(!board->isThinking && board->getWinner() == -1){
        board->isThinking = true;
        if(board->currentPlayer==0)
            firstAIPlay();
        else
            secondAIPlay();
        board->isThinking = false;
    }
}
void GameScene::gameOverProcess(int winner){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite* sp;
    if(winner == 0)
        sp = Sprite::create("gameover_blue.png");
	// TODO: draw game
    else if(winner == 1 || winner == 2)
        sp = Sprite::create("gameover_red.png");
    sp->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    auto restartItem = MenuItemImage::create ("restart_normal.png",
                                              "restart_press.png",CC_CALLBACK_1(GameScene::menuRestartCallback, this));
    auto backToMainItem = MenuItemImage::create ("back_normal.png",
                                                 "back_press.png",CC_CALLBACK_1(GameScene::menuBackToMainCallback, this));
    restartItem->setPosition(Point(visibleSize.width/2-restartItem->getContentSize().width/2-30,
                                   visibleSize.height/2-restartItem->getContentSize().height+40));
    backToMainItem->setPosition(Point(visibleSize.width/2+backToMainItem->getContentSize().width/2+30,
                                   visibleSize.height/2-backToMainItem->getContentSize().height+40));
    

    auto menu = Menu::create(restartItem,backToMainItem,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(sp);
    this->addChild(menu, 1);

}
void GameScene::operatePieceVsPeople(PointXY chosenBlock){
    if (chosenBlock.x < 0 || chosenBlock.y < 0)
        return;
    if (chosenBlock.x > 8 || chosenBlock.y>6)
        return;
    auto clickedPiece = board->getPiece(chosenBlock);
    // if no piece has been choosen yet
    if (board->selected->getType() == Pieces::NIL) {
        // cannot choose opponent's piece
        if (board->currentPlayer != clickedPiece->getPlayer())
            return;
        //  choose this piece and highlight it
        board->selected = clickedPiece;
        // if the piece exists, highlight
        if (clickedPiece->getType() != Pieces::NIL)
            clickedPiece->highlight();
    } else {
        PointXY from = board->selected->getPositionBlock();
        if (board->availableMove(Move{ from,chosenBlock })) {
            Move move = { board->selected->getPositionBlock(),chosenBlock };
            board->moveChess(move);
			gameOverDetect();
        } else {
            //reset
            board->selected->recover();
            board->selected = board->nul_piece;
        }
    }
}
void GameScene::operatePieceVsAI(PointXY chosenBlock){
    if (chosenBlock.x < 0 || chosenBlock.y < 0)
        return;
    if (chosenBlock.x > 8 || chosenBlock.y>6)
        return;
    auto clickedPiece = board->getPiece(chosenBlock);
    if(board->currentPlayer==0){
        if (board->selected->getType() == Pieces::NIL) {
            if (board->currentPlayer != clickedPiece->getPlayer())
                return;
            board->selected = clickedPiece;
            if (clickedPiece->getType() != Pieces::NIL)
                clickedPiece->highlight();
        } else {
            PointXY from = board->selected->getPositionBlock();
            if (board->availableMove(Move{ from,chosenBlock })) {
                Move move = { board->selected->getPositionBlock(),chosenBlock };
                board->moveChess(move);
                int winner = board->getWinner();
				if (winner == -1)
					this->scheduleOnce(schedule_selector(GameScene::onceUpdate), 0.01f);
				else
					gameOverProcess(winner);
            } else {
                board->selected->recover();
                board->selected = board->nul_piece;
            }
        }
    }
}
void GameScene::onceUpdate(float dt){
    if(gameMode==1){
        if(board->currentPlayer==1){
            std::cout<<"Minimax take step."<<std::endl;
			auto mv = MinMax->getMove(5, 1);
			board->moveChess(mv);
			gameOverDetect();
        }
    }
    if (gameMode==2){
        if(board->currentPlayer==1){
            std::cout<<"MCTS take step."<<std::endl;
            board->currentPlayer=0;
        }
    }
}
void GameScene::firstAIPlay(){
    auto mv = MinMax->getMove(3, 0);
    board->moveChess(mv,true);
    if(gameOverDetect()){
        finishEvolutionProcess();
        if(!Evolution::GetInstance()->evolutionEnd){
            Scene* newGame = GameScene::createScene();
            auto transition = TransitionCrossFade::create(0.5f, newGame);
            Director::getInstance()->replaceScene(transition);
        }
        
    }
}
void GameScene::secondAIPlay(){
    auto mv = MinMax->getMove(3, 1);
    board->moveChess(mv,true);
    if(gameOverDetect()){
        finishEvolutionProcess();
        if(!Evolution::GetInstance()->evolutionEnd){
            Scene* newGame = GameScene::createScene();
            auto transition = TransitionCrossFade::create(0.5f, newGame);
            Director::getInstance()->replaceScene(transition);
        }
    }
}
bool GameScene::gameOverDetect(){
	int winner = board->getWinner();
  	if ( winner != -1) {
        cout <<endl<< "GameOver player "<<winner<<" win" << endl;
		gameOverProcess(winner);
        return true;
	}
    else
        return false;
}
void GameScene::menuRestartCallback(cocos2d::Ref* pSender){
     Scene* newGame = GameScene::createScene();
     auto transition = TransitionCrossFade::create(0.5f, newGame);
     Director::getInstance()->replaceScene(transition);
}
void GameScene::menuBackToMainCallback(cocos2d::Ref* pSender){
    Scene* main = HelloWorld::createScene();
    auto transition = TransitionCrossFade::create(0.5f, main);
    Director::getInstance()->replaceScene(transition);
}

