#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameLoop.h"

class GameState :public State {
public:
	GameState(GameDataRef data);
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);
private:
	void initGridPiece();

	GameDataRef _data;
	sf::Sprite _background;
	sf::Sprite _pauseButton;
	sf::Sprite _gridSprite;

	sf::Sprite _gridPieces[3][3];
	int gridArray[3][3];

	int turn;
	int gameState;
};