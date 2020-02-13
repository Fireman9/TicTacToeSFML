#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetMng.h"
#include "InputMng.h"

namespace Sonar {
	struct GameData {
		StateMachine machine;
		sf::RenderWindow window;
		AssetMng assets;
		InputMng input;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class GameLoop{
	public:
		GameLoop(int width, int height, std::string title);
	private:
		const float dt = 1.0f / 60.0f;
		sf::Clock _clock;

		GameDataRef _data = std::make_shared<GameData>();

		void run();
	};
}
