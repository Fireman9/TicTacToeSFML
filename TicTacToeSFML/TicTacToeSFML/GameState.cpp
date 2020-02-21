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

	this->_data->assets.loadTexture("Pause Button", PAUSE_BUTTON);

	_background.setTexture(this->_data->assets.getTexture("Background"));
	_pauseButton.setTexture(this->_data->assets.getTexture("Pause Button"));

	_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
}

void GameState::handleInput() {
	sf::Event event;
	while (this->_data->window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			this->_data->window.close();
		}
		if (this->_data->input.isSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window)) {
			//this->_data->machine.addState(StateRef(new PauseState(_data)), false);
			this->_data->machine.addState(StateRef(new GameOverState(_data)), true);
		}
	}
}

void GameState::update(float dt) {

}

void GameState::draw(float dt) {
	this->_data->window.clear();
	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_pauseButton);
	this->_data->window.display();
}