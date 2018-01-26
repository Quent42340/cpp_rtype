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
#include "SpriteLoader.hpp"
#include "Sprite.hpp"
#include "XMLFile.hpp"

void SpriteLoader::load(const char *xmlFilename, ResourceHandler &handler) {
	XMLFile doc(xmlFilename);

	tinyxml2::XMLElement *spriteElement = doc.FirstChildElement("animations").FirstChildElement("sprite").ToElement();
	while (spriteElement) {
		std::string name = spriteElement->Attribute("name");
		u16 frameWidth = spriteElement->IntAttribute("width");
		u16 frameHeight = spriteElement->IntAttribute("height");

		Sprite &sprite = handler.add<Sprite>(name + "-sprite", name, frameWidth, frameHeight);

		tinyxml2::XMLElement *animationElement = spriteElement->FirstChildElement("animation");
		while (animationElement) {
			u32 delay = animationElement->IntAttribute("delay");
			bool isLoop = animationElement->IntAttribute("loop");

			SpriteAnimation animation(delay, isLoop);

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

