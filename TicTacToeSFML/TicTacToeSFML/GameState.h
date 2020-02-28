#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameLoop.h"
#include "AI.h"

class GameState :public State {
public:
	GameState(GameDataRef data);
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);
private:
	void initGridPiece();
	void checkAndPlace();
	void checkPlayerWon(int turn);
	void check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);

	GameDataRef _data;
	sf::Sprite _background;
	sf::Sprite _pauseButton;
	sf::Sprite _gridSprite;

	sf::Sprite _gridPieces[3][3];
	int gridArray[3][3];

	int turn;
	int gameState;

	AI* ai;

	sf::Clock _clock;
};