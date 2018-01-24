/*
 * =====================================================================================
 *
 *       Filename:  AudioPlayer.cpp
 *
 *    Description:
 *
 *        Created:  24/01/2018 04:48:48
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <SFML/Audio/Music.hpp>

#include "AudioPlayer.hpp"
#include "ResourceHandler.hpp"

std::string AudioPlayer::s_currentMusic;

void AudioPlayer::playMusic(const std::string &resourceName) {
	if (!s_currentMusic.empty())
		ResourceHandler::getInstance().get<sf::Music>(s_currentMusic).stop();
	ResourceHandler::getInstance().get<sf::Music>(resourceName).setVolume(70);
	ResourceHandler::getInstance().get<sf::Music>(resourceName).play();
	s_currentMusic = resourceName;
}

