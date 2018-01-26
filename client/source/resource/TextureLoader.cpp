/*
 * =====================================================================================
 *
 *       Filename:  TextureLoader.cpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:49:49
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <SFML/Graphics/Texture.hpp>

#include "TextureLoader.hpp"
#include "XMLFile.hpp"

void TextureLoader::load(const char *xmlFilename, ResourceHandler &handler) {
	XMLFile doc(xmlFilename);

	tinyxml2::XMLElement *textureElement = doc.FirstChildElement("textures").FirstChildElement("texture").ToElement();
	while(textureElement) {
		std::string folder = textureElement->Attribute("folder");
		std::string name = textureElement->Attribute("name");

		sf::Texture &texture = handler.add<sf::Texture>(folder + "-" + name);
		texture.loadFromFile("graphics/" + folder + "/" + name + ".png");

		textureElement = textureElement->NextSiblingElement("texture");
	}
}

