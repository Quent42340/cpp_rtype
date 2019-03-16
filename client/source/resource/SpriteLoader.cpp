/*
 * =====================================================================================
 *
 *       Filename:  SpriteLoader.cpp
 *
 *    Description:
 *
 *        Created:  25/01/2018 03:47:44
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/core/XMLFile.hpp>
#include <gk/graphics/Sprite.hpp>
#include <gk/resource/ResourceHandler.hpp>

#include "SpriteLoader.hpp"

void SpriteLoader::load(const char *xmlFilename, gk::ResourceHandler &handler) {
	gk::XMLFile doc(xmlFilename);

	tinyxml2::XMLElement *spriteElement = doc.FirstChildElement("animations").FirstChildElement("sprite").ToElement();
	while (spriteElement) {
		std::string name = spriteElement->Attribute("name");
		u16 frameWidth = spriteElement->IntAttribute("width");
		u16 frameHeight = spriteElement->IntAttribute("height");

		gk::Sprite &sprite = handler.add<gk::Sprite>(name + "-sprite", "texture-" + name, frameWidth, frameHeight);

		tinyxml2::XMLElement *animationElement = spriteElement->FirstChildElement("animation");
		if (animationElement) sprite.setAnimated(true);
		while (animationElement) {
			u32 delay = animationElement->IntAttribute("delay");
			bool isLoop = animationElement->IntAttribute("loop");

			gk::SpriteAnimation animation(delay, isLoop);

			tinyxml2::XMLElement *frameElement = animationElement->FirstChildElement("frame");
			while (frameElement) {
				u8 frameId = frameElement->IntAttribute("id");

				animation.addFrame(frameId);

				frameElement = frameElement->NextSiblingElement("frame");
			}

			sprite.addAnimation(animation);

			animationElement = animationElement->NextSiblingElement("animation");
		}

		spriteElement = spriteElement->NextSiblingElement("sprite");
	}
}

