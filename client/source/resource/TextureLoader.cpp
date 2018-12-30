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
#include <gk/core/XMLFile.hpp>
#include <gk/gl/Texture.hpp>
#include <gk/resource/ResourceHandler.hpp>

#include "TextureLoader.hpp"

void TextureLoader::load(const char *xmlFilename, gk::ResourceHandler &handler) {
	gk::XMLFile doc(xmlFilename);

	tinyxml2::XMLElement *textureElement = doc.FirstChildElement("textures").FirstChildElement("texture").ToElement();
	while(textureElement) {
		std::string folder = textureElement->Attribute("folder");
		std::string name = textureElement->Attribute("name");

		gk::Texture &texture = handler.add<gk::Texture>(folder + "-" + name);
		texture.loadFromFile("resources/graphics/" + folder + "/" + name + ".png");

		textureElement = textureElement->NextSiblingElement("texture");
	}
}

