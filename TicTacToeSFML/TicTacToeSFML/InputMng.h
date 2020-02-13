#pragma once

#include "SFML/Graphics.hpp"

namespace Sonar {
	class InputMng{
	public:
		InputMng() {

		}
		~InputMng() {

		}
		bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);
		sf::Vector2i getMousePosition(sf::RenderWindow& window);
	};
}