#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "GameLoop.h"

class SplashState :public State {
public:
	SplashState(GameDataRef data);

	void init();

	void handleInput();
	void update(float dt);
	void draw(float dt);

private:
	GameDataRef _data;
	sf::Clock _clock;
	sf::Sprite _background;
};

