#include "SplashState.h"
#include <sstream>
#include <iostream>
#include "Definitions.h"


SplashState::SplashState(GameDataRef data) :_data(data){

}

void SplashState::init(){
	this->_data->assets.loadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
	_background.setTexture(this->_data->assets.getTexture("Splash State Background"));
}

void SplashState::handleInput(){
	sf::Event event;
	while (this->_data->window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			this->_data->window.close();
		}
	}
}

void SplashState::update(float dt){
	if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME) {
		//Switch to Main Menu
		std::cout << "Go to Main Menu" << std::endl;
	}
}

void SplashState::draw(float dt){
	this->_data->window.clear(sf::Color::Red);
	this->_data->window.draw(this->_background);
	this->_data->window.display();
}
