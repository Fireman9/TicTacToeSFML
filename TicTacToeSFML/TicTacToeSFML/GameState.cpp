#include "GameState.h"
#include <sstream>
#include "Definitions.h"
#include "PauseState.h"
#include "GameOverState.h"
#include <iostream>

GameState::GameState(GameDataRef data) :_data(data) {

}

void GameState::init() {
	gameState = STATE_PLAYING;
	turn = PLAYER_PIECE;

	this->ai = new AI(turn, this->_data);

	this->_data->assets.loadTexture("Pause Button", PAUSE_BUTTON);
	this->_data->assets.loadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
	this->_data->assets.loadTexture("X Piece", X_PIECE_FILEPATH);
	this->_data->assets.loadTexture("O Piece", O_PIECE_FILEPATH);
	this->_data->assets.loadTexture("X Winning Piece", X_WINNING_PIECE_FILEPATH);
	this->_data->assets.loadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);

	_background.setTexture(this->_data->assets.getTexture("Background"));
	_pauseButton.setTexture(this->_data->assets.getTexture("Pause Button"));
	_gridSprite.setTexture(this->_data->assets.getTexture("Grid Sprite"));

	_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
	_gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2), (SCREEN_HEIGTH / 2) - (_gridSprite.getGlobalBounds().height / 2));

	initGridPiece();

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			gridArray[x][y] = EMPTY_PIECE;
		}
	}
}

void GameState::handleInput() {
	sf::Event event;
	while (this->_data->window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			this->_data->window.close();
		}
		if (this->_data->input.isSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window)) {
			this->_data->machine.addState(StateRef(new PauseState(_data)), false);
		}
		else if (this->_data->input.isSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window)) {
			if (STATE_PLAYING == gameState) {
				this->checkAndPlace();
			}
		}
	}
}

void GameState::update(float dt) {
	if (STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState) {
		if (this->_clock.getElapsedTime().asSeconds() > TIME_BEFORE_SHOWING_GAME_OVER) {
			this->_data->machine.addState(StateRef(new GameOverState(_data)), true);
		}
	}
}

void GameState::draw(float dt) {
	this->_data->window.clear();
	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_pauseButton);
	this->_data->window.draw(this->_gridSprite);

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			this->_data->window.draw(this->_gridPieces[x][y]);
		}
	}

	this->_data->window.display();
}

void GameState::initGridPiece() {
	sf::Vector2u tempSpriteSize = this->_data->assets.getTexture("X Piece").getSize();

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			_gridPieces[x][y].setTexture(this->_data->assets.getTexture("X Piece"));
			_gridPieces[x][y].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x * x) - 7, _gridSprite.getPosition().y + (tempSpriteSize.y * y) - 7);
			_gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
		}
	}
}

void GameState::checkAndPlace() {
	sf::Vector2i touchPoint = this->_data->input.getMousePosition(this->_data->window);
	sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
	sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGTH - gridSize.height) / 2);
	sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);
	sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);
	int column, row;

	if (gridLocalTouchPos.x < gridSectionSize.x) {
		column = 1;
	}
	else if (gridLocalTouchPos.x < gridSectionSize.x * 2) {
		column = 2;
	}
	else if (gridLocalTouchPos.x < gridSize.width) {
		column = 3;
	}
	if (gridLocalTouchPos.y < gridSectionSize.y) {
		row = 1;
	}
	else if (gridLocalTouchPos.y < gridSectionSize.y * 2) {
		row = 2;
	}
	else if (gridLocalTouchPos.y < gridSize.height) {
		row = 3;
	}

	if (gridArray[column - 1][row - 1] == EMPTY_PIECE) {
		gridArray[column - 1][row - 1] = turn;
		if (PLAYER_PIECE == turn) {
			_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.getTexture("X Piece"));
			this->checkPlayerWon(turn);
		}

		_gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));
	}
}

void GameState::checkPlayerWon(int turn) {
	check3PiecesForMatch(0, 0, 1, 0, 2, 0, turn);
	check3PiecesForMatch(0, 1, 1, 1, 2, 1, turn);
	check3PiecesForMatch(0, 2, 1, 2, 2, 2, turn);
	check3PiecesForMatch(0, 0, 0, 1, 0, 2, turn);
	check3PiecesForMatch(1, 0, 1, 1, 1, 2, turn);
	check3PiecesForMatch(2, 0, 2, 1, 2, 2, turn);
	check3PiecesForMatch(0, 0, 1, 1, 2, 2, turn);
	check3PiecesForMatch(0, 2, 1, 1, 2, 0, turn);

	if (STATE_WON != gameState) {
		gameState = STATE_AI_PLAYING;

		ai->PlacePiece(&gridArray, _gridPieces, &gameState);

		check3PiecesForMatch(0, 0, 1, 0, 2, 0, AI_PIECE);
		check3PiecesForMatch(0, 1, 1, 1, 2, 1, AI_PIECE);
		check3PiecesForMatch(0, 2, 1, 2, 2, 2, AI_PIECE);
		check3PiecesForMatch(0, 0, 0, 1, 0, 2, AI_PIECE);
		check3PiecesForMatch(1, 0, 1, 1, 1, 2, AI_PIECE);
		check3PiecesForMatch(2, 0, 2, 1, 2, 2, AI_PIECE);
		check3PiecesForMatch(0, 0, 1, 1, 2, 2, AI_PIECE);
		check3PiecesForMatch(0, 2, 1, 1, 2, 0, AI_PIECE);
	}

	int emptyNum = 9;

	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (EMPTY_PIECE != gridArray[x][y]) {
				emptyNum--;
			}
		}
	}
	if (0 == emptyNum && (STATE_WON != gameState) && (STATE_LOSE != gameState)) {
		gameState = STATE_DRAW;
	}
	if (STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState) {
		this->_clock.restart();
	}

	std::cout << gameState << std::endl;
}

void GameState::check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck) {
	if (pieceToCheck == gridArray[x1][y1] && pieceToCheck == gridArray[x2][y2] && pieceToCheck == gridArray[x3][y3]) {
		std::string winningPieceStr;
		if (O_PIECE == pieceToCheck) {
			winningPieceStr = "O Winning Piece";
		}
		else {
			winningPieceStr = "X Winning Piece";
		}

		_gridPieces[x1][y1].setTexture(this->_data->assets.getTexture(winningPieceStr));
		_gridPieces[x2][y2].setTexture(this->_data->assets.getTexture(winningPieceStr));
		_gridPieces[x3][y3].setTexture(this->_data->assets.getTexture(winningPieceStr));
	
		if (PLAYER_PIECE == pieceToCheck) {
			gameState = STATE_WON;
		}
		else {
			gameState = STATE_LOSE;
		}
	}
}
