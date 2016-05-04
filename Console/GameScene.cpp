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



bool GameScene::init() {
	releaseMem();
	board = new Board();
	MinMax = new AI_Min_Max(board);
	gameMode = -1;
	startEvolutionPrcess();
	return true;
}

void GameScene::startEvolutionPrcess() {
	auto E = Evolution::GetInstance();

	for (int i = 2; i < board->allPieces.size(); i++) {
		board->allPieces[i]->setGene(E->population[E->p1],0);
		board->allPieces[i]->setGene(E->population[E->p2],1);
	}
}



void GameScene::finishEvolutionProcess() {
	auto E = Evolution::GetInstance();

	
	int populationNum = E->population.size();
	auto &p1 = E->p1;
	auto &p2 = E->p2;
	
	cout << "current pair are gene " << p1 << " and gene " << p2 << endl;
	cout << "current left generation " << E->getGenerationNum() << endl;

	auto winner = board->getWinner();
	if (winner == 2) {
		E->population[p2].drawGames++;
		E->population[p1].drawGames++;
	} else if (winner == 1) {
		E->population[p2].winGames++;
		E->population[p1].loseGames++;
	} else {
		E->population[p1].winGames++;
		E->population[p2].loseGames++;
	}

	// Debug
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
			//Evolution::GetInstance()->generationNum = 1;
			gameOverProcess(board->getWinner());//evolution end
		} else {
			p1 = 0;
			p2 = 1;
			E->storePopulationGenes();
		}
	}

	

	/*
	auto winner = board->getWinner();
	ofstream fout("result.txt", ofstream::app);
	if(winner == 2)
	fout<<p1<<"\t"<< p2 <<"\tdraw"<<endl;
	else if(winner == 1)
	fout<< p1 <<"\t"<< p2 <<"\tlose"<<endl;
	else if(winner == 0)
	fout<< p1 <<"\t"<< p2 <<"\twin"<<endl;

	E->p2++;
	if(E->p2 == E->population.size()){
		E->p1++;
		E->p2 = 20;
	}
	if( p1 == 17 ){
		E->evolutionEnd = true;
		gameOverProcess(winner);
	}
	fout.close();
	*/
	
}

void GameScene::releaseMem()
{
	if (board)
		delete board;
	if (MinMax)
		delete MinMax;
	board = NULL;
	MinMax = NULL;
}

void GameScene::run()
{
	init();
	char buff[32];
	cout << "Select Game Mode  0, 1 or 2 :";
	gameMode = -1;
	while (gameMode == -1) {
		cin >> buff;
		gameMode = buff[0] - '0';
	}
	bool running = true;
	while (running) {
		switch (gameMode) {
		case 0:
		{
			board->fcoutBoard();
			cin >> buff;
			if (isdigit(buff[0]) && isdigit(buff[1]) && isdigit(buff[2]) && isdigit(buff[3])) {
				buff[0] -= 48; buff[1] -= 48; buff[2] -= 48; buff[3] -= 48;
				Move move{ PointXY(buff[0],buff[1]),PointXY(buff[2],buff[3]) };
				operatePieceVsPeople(move);
			}
		}break;
		case 1:
		{
			board->fcoutBoard();
			cin >> buff;
			if (isdigit(buff[0]) && isdigit(buff[1]) && isdigit(buff[2]) && isdigit(buff[3])) {
				buff[0] -= 48; buff[1] -= 48; buff[2] -= 48; buff[3] -= 48;
				Move move{ PointXY(buff[0],buff[1]),PointXY(buff[2],buff[3]) };
				operatePieceVsAI(move);
			}
		}break;
		case 2:
		{
			competetition();
		}break;

		default: running = false; break;
		}
	}
}

void GameScene::competetition()
{
	if (!board->isThinking && board->getWinner() == -1) {
		board->isThinking = true;
		if (board->currentPlayer == 0)
			firstAIPlay();
		else
			secondAIPlay();
		board->isThinking = false;
	}
}

void GameScene::update() {
	if (!board->isThinking && board->getWinner() == -1) {
		board->isThinking = true;
		if (board->currentPlayer == 0)
			firstAIPlay();
		else
			secondAIPlay();
		board->isThinking = false;
	}
}
void GameScene::gameOverProcess(int winner) {
	if (gameMode != 2) {
		cout << "Game Over\nWinner is:" << winner << endl;
		cout << "Restart? (y/n)" << endl;
		while (1) {
			char ch = getchar();
			if (ch == 'y') {
				init();
				break;
			} else if (ch == 'n') {
				break;
			} else {
				continue;
			}
		}
	}
}

void GameScene::operatePieceVsPeople(Move move) {
	auto from = move.from;
	auto to = move.to;
	if (from.x < 0 || from.y < 0 || to.x < 0 || to.y < 0 || from.x > 8 || from.y > 6 || to.x > 8 || to.y > 6)
		return;
	if (board->getPiece(from)->getPlayer() == board->currentPlayer && board->availableMove(move)) {
		board->moveChess(move);
		gameOverDetect();
	}
}
void GameScene::operatePieceVsAI(Move move) {
	auto from = move.from;
	auto to = move.to;
	if (from.x < 0 || from.y < 0 || to.x < 0 || to.y < 0 || from.x > 8 || from.y > 6 || to.x > 8 || to.y > 6)
		return;
	if (board->currentPlayer == 0) {
		if (board->availableMove(move)) {
			board->moveChess(move);
			int winner = board->getWinner();
			if (winner == -1) {
				onceUpdate();
			} else {
				gameOverProcess(winner);
			}
		}
	}

}
void GameScene::onceUpdate() {
	if (gameMode == 1) {
		if (board->currentPlayer == 1) {
			std::cout << "Minimax take step." << std::endl;
			auto mv = MinMax->getMove(6, 1);
			board->moveChess(mv);
			gameOverDetect();
		}
	}
	if (gameMode == 2) {
		if (board->currentPlayer == 1) {
			std::cout << "MCTS take step." << std::endl;
			board->currentPlayer = 0;
		}
	}
}

void GameScene::firstAIPlay() {
	auto mv = MinMax->getMove(4, 0);
	board->moveChess(mv, true);
	if (gameOverDetect()) {
		finishEvolutionProcess();
		if (!Evolution::GetInstance()->evolutionEnd) {
			init();
			gameMode = 2;
		} else {
			gameMode = -1;
		}
	}
}

void GameScene::secondAIPlay() {
	auto mv = MinMax->getMove(4, 1);
	board->moveChess(mv, true);
	if (gameOverDetect()) {
		finishEvolutionProcess();
		if (!Evolution::GetInstance()->evolutionEnd) {
			init();
			gameMode = 2;
		} else {
			gameMode = -1;
		}
	}
}
bool GameScene::gameOverDetect() {
	int winner = board->getWinner();
	if (winner != -1) {
		cout <<endl<< "GameOver player "<<winner<<" win" << endl;
		gameOverProcess(winner);
		return true;
	} else
		return false;
}
