#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameLoop.h"

class PauseState :public State {
public:
	PauseState(GameDataRef data);
	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);
private:
	GameDataRef _data;
	sf::Sprite _background;
	sf::Sprite _resumeButton;
	sf::Sprite _homeButton;
};