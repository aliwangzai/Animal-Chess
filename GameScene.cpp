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
    //std::cout<<gameMode<<std::endl;

    TMXTiledMap* gameMap = TMXTiledMap::create("gameMap.tmx");
    this->addChild(gameMap);
    board = new Board();
    board->initPieces(gameMap);
	MinMax = new AI_Min_Max(board);
    startEvolutionPrcess();
    
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
    //Evolution::GetInstance()->loadPopulationGenes();
    int pairnum =Evolution::GetInstance()->currentPairNum;
    int populationNum =Evolution::GetInstance()->population.size();
    Gene gene0 = Evolution::GetInstance()->population[pairnum];
    Gene gene1 = Evolution::GetInstance()->population[populationNum-1-pairnum];
    for(int i =2; i< board->allPieces.size();i++){
		if (board->allPieces[i]->getPlayer() == 0)
			board->allPieces[i]->setGene(gene0);
		else
			board->allPieces[i]->setGene(gene1);
    }

    
    
}
void GameScene::finishEvolutionProcess(){
    int pairnum =Evolution::GetInstance()->currentPairNum;
    int populationNum =Evolution::GetInstance()->population.size();
    cout<<"current pair are gene "<<pairnum<<" and gene "<<populationNum-1-pairnum<<endl;
    cout<<"current left generation "<<Evolution::GetInstance()->getGenerationNum()<<endl;
    
    /*
    int winner = -1;
    if(board->getWinner() == 2){
        Player eval;
        winner = eval.eval(*board) < 0;
    }else{
        winner = board->getWinner();
    }
    */
    if(board->getWinner() == 2){
        Gene m_gene ;
        m_gene.generateRandomGene();
        Evolution::GetInstance()->population[pairnum] = m_gene;
        m_gene.printGene();
        Evolution::GetInstance()->population[populationNum-1-pairnum] = m_gene;
        Evolution::GetInstance()->population[pairnum].printGene();

        Evolution::GetInstance()->population[pairnum].winState = 1;
        Evolution::GetInstance()->population[populationNum-1-pairnum].winState = -1;

    }
    else if(board->getWinner()){
        Evolution::GetInstance()->population[pairnum].winState = 1;
        Evolution::GetInstance()->population[populationNum-1-pairnum].winState = -1;
    }
    else{
        Evolution::GetInstance()->population[pairnum].winState = -1;
        Evolution::GetInstance()->population[populationNum-1-pairnum].winState = 1;
    }
    
    if(Evolution::GetInstance()->currentPairNum != Evolution::GetInstance()->population.size()/2-1){ //not all pairs finish their game
        Evolution::GetInstance()->currentPairNum++;
    }
    else{//all pair finish game
        Evolution::GetInstance()->select();
        if(Evolution::GetInstance()->getGenerationNum()==0){
            Evolution::GetInstance()->storePopulationGenes();
            Evolution::GetInstance()->evolutionEnd = true;
            //Evolution::GetInstance()->generationNum = 1;
            gameOverProcess(board->getWinner());//evolution end
        }
        else{
            Evolution::GetInstance()->currentPairNum = 0;
            Evolution::GetInstance()->storePopulationGenes();
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
				if (int winner = board->getWinner() == -1)
					this->scheduleOnce(schedule_selector(GameScene::onceUpdate), 0.01f);
				else
					gameOverProcess(winner);
            } else {
                //reset
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
			auto mv = MinMax->getMove(3, 1);
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
    auto mv = MinMax->getMove(2, 0);
    board->moveChess(mv,true);
    //std::cout<<"Minimax1 take step."<<std::endl;
    if(gameOverDetect()){
        cout<<"GameOver player0 win"<<endl;
        finishEvolutionProcess();
        if(!Evolution::GetInstance()->evolutionEnd){
            Scene* newGame = GameScene::createScene();
            auto transition = TransitionCrossFade::create(0.5f, newGame);
            Director::getInstance()->replaceScene(transition);
        }
    }
}
void GameScene::secondAIPlay(){
    
    auto mv = MinMax->getMove(2, 1);
    board->moveChess(mv,true);
    //std::cout<<"Minimax2 take step."<<std::endl;
    if(gameOverDetect()){
        cout<<"GameOver player1 win"<<endl;
        finishEvolutionProcess();
        if(!Evolution::GetInstance()->evolutionEnd){
        Scene* newGame = GameScene::createScene();
        auto transition = TransitionCrossFade::create(0.5f, newGame);
        Director::getInstance()->replaceScene(transition);
        }
    }
}
bool GameScene::gameOverDetect(){
	if (int winner = board->getWinner() != -1) {
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
