#include "MainMenuState.h"
#include <sstream>
#include "Definitions.h"
#include "GameState.h"
#include <iostream>

MainMenuState::MainMenuState(GameDataRef data):_data(data){

}

void MainMenuState::init(){
	this->_data->assets.loadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
	this->_data->assets.loadTexture("Play Button", MAIN_MENU_PLAY_BUTTON_FILEPATH);
	this->_data->assets.loadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER_FILEPATH);
	this->_data->assets.loadTexture("Game Title", MAIN_MENU_TITLE_FILEPATH);
	this->_background.setTexture(this->_data->assets.getTexture("Background"));
	this->_playButton.setTexture(this->_data->assets.getTexture("Play Button"));
	this->_playButtonOuter.setTexture(this->_data->assets.getTexture("Play Button Outer"));
	this->_title.setTexture(this->_data->assets.getTexture("Game Title"));
	
	this->_playButton.setPosition((SCREEN_WIDTH / 2) - (this->_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGTH / 2) - (this->_playButton.getGlobalBounds().height / 2));
	this->_playButtonOuter.setPosition((SCREEN_WIDTH / 2) - (this->_playButtonOuter.getGlobalBounds().width / 2), (SCREEN_HEIGTH / 2) - (this->_playButtonOuter.getGlobalBounds().height / 2));
	this->_title.setPosition((SCREEN_WIDTH / 2) - (this->_title.getGlobalBounds().width / 2), this->_title.getGlobalBounds().height * 0.1);
}

void MainMenuState::handleInput(){
	sf::Event event;
	while (this->_data->window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			this->_data->window.close();
		}
		if (this->_data->input.isSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->window)) {
			this->_data->machine.addState(StateRef(new GameState(_data)), true);
		}
	}
}

void MainMenuState::update(float dt){

}

void MainMenuState::draw(float dt){
	this->_data->window.clear();
	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_playButton);
	this->_data->window.draw(this->_playButtonOuter);
	this->_data->window.draw(this->_title);
	this->_data->window.display();
}