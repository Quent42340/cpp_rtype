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
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <gk/core/XMLFile.hpp>
#include <gk/resource/ResourceHandler.hpp>

#include "AudioLoader.hpp"

void AudioLoader::load(const char *xmlFilename, gk::ResourceHandler &handler) {
	gk::XMLFile doc(xmlFilename);

	tinyxml2::XMLElement *rootElement = doc.FirstChildElement("audio").ToElement();
	tinyxml2::XMLElement *musicElement = rootElement->FirstChildElement("music");
	while(musicElement) {
		std::string name = musicElement->Attribute("name");
		int volume = musicElement->IntAttribute("volume");

		sf::Music &music = handler.add<sf::Music>("music-" + name);
		music.openFromFile("resources/audio/music/" + name + ".ogg");
		music.setVolume(volume);

		musicElement = musicElement->NextSiblingElement("music");
	}

	tinyxml2::XMLElement *soundElement = rootElement->FirstChildElement("sound");
	while(soundElement) {
		std::string name = soundElement->Attribute("name");
		int volume = soundElement->IntAttribute("volume");

		sf::SoundBuffer &buffer = handler.add<sf::SoundBuffer>("soundbuffer-" + name);
		buffer.loadFromFile("resources/audio/sound/" + name + ".wav");

		sf::Sound &sound = handler.add<sf::Sound>("sound-" + name, buffer);
		sound.setVolume(volume);

		soundElement = soundElement->NextSiblingElement("sound");
	}
}

