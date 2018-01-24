/*
 * =====================================================================================
 *
 *       Filename:  AudioLoader.cpp
 *
 *    Description:
 *
 *        Created:  24/01/2018 21:33:39
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <SFML/Audio/Music.hpp>

#include "AudioLoader.hpp"
#include "XMLFile.hpp"

void AudioLoader::load(const char *xmlFilename, ResourceHandler &handler) {
	XMLFile doc(xmlFilename);

	tinyxml2::XMLElement *rootElement = doc.FirstChildElement("audio").ToElement();
	tinyxml2::XMLElement *musicElement = rootElement->FirstChildElement("music");
	while(musicElement) {
		std::string name = musicElement->Attribute("name");
		int volume = musicElement->IntAttribute("volume");

		sf::Music &music = handler.add<sf::Music>("music-" + name);
		music.openFromFile("audio/music/" + name + ".ogg");
		music.setVolume(volume);

		musicElement = musicElement->NextSiblingElement("music");
	}

	tinyxml2::XMLElement *soundElement = rootElement->FirstChildElement("sound");
	while(soundElement) {
		std::string name = soundElement->Attribute("name");
		int volume = soundElement->IntAttribute("volume");

		sf::Music &music = handler.add<sf::Music>("sound-" + name);
		music.openFromFile("audio/sound/" + name + ".ogg");
		music.setVolume(volume);

		soundElement = soundElement->NextSiblingElement("sound");
	}
}

