#include "AssetMng.h"

namespace Sonar {
	void AssetMng::loadTexture(std::string name, std::string fileName) {
		sf::Texture text;
		if (text.loadFromFile(fileName)) {
			this->_textures[name] = text;
		}
	}
	sf::Texture& AssetMng::getTexture(std::string name){
		return this->_textures.at(name);
	}
	void AssetMng::loadFont(std::string name, std::string fileName){
		sf::Font font;
		if (font.loadFromFile(fileName)) {
			this->_fonts[name] = font;
		}
	}
	sf::Font& AssetMng::getFont(std::string name){
		return this->_fonts.at(name);
	}
}