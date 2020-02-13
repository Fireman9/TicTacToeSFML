#include <SFML/Graphics.hpp>

#include <iostream>

using namespace sf;

int main() {
	RenderWindow window(VideoMode(1024, 1024), "TicTacToeSFML");

	while(window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		window.clear();

		window.display();
	}

	return 0;
}