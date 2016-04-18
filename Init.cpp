bool GameScene::init() {
	if (!Layer::init()) {
		return false;
	}

	board = new Board();

	TMXTiledMap* gameMap = TMXTiledMap::create("gameMap.tmx");
	this->addChild(gameMap);
	board->initPieces(gameMap);

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
				// 我把游戏结束判断封装到了一个函数因为AI也需要有用到__lwl
				if (int winner = board->getWinner() != -1) {
					gameOverProcess(winner);
				}
				//GameScene::gameOver=true;
			} else {
				//reset
				board->selected->recover();
				board->selected = board->nul_piece;
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}