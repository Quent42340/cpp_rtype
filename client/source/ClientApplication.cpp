/*
 * =====================================================================================
 *
 *       Filename:  ClientClientApplication.cpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 00:31:02
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/core/input/GamePad.hpp>
#include <gk/resource/AudioPlayer.hpp>
#include <gk/resource/TextureLoader.hpp>

#include "AudioLoader.hpp"
#include "ClientApplication.hpp"
#include "Config.hpp"
#include "GameState.hpp"
#include "SpriteLoader.hpp"
#include "TitleScreenState.hpp"

void ClientApplication::init() {
	gk::CoreApplication::init();

	m_window.create(sf::VideoMode(Config::screenWidth, Config::screenHeight), "R-Type", sf::Style::Close);

	gk::GamePad::init(m_keyboardHandler);

	m_resourceHandler.loadConfigFile<AudioLoader>("resources/config/audio.xml");
	m_resourceHandler.loadConfigFile<gk::TextureLoader>("resources/config/textures.xml");
	m_resourceHandler.loadConfigFile<SpriteLoader>("resources/config/sprites.xml");
	m_resourceHandler.add<sf::Font>("font-default").loadFromFile("resources/fonts/arial.ttf");
	m_resourceHandler.add<sf::Font>("font-pdark").loadFromFile("resources/fonts/pdark.ttf");

	gk::ApplicationStateStack::getInstance().push<TitleScreenState>();
}

void ClientApplication::onEvent(const sf::Event &event) {
	gk::CoreApplication::onEvent(event);

	// if (event.type == sf::Event::GainedFocus) {
	// 	gk::AudioPlayer::resumeMusic();
	// }
	// else if (event.type == sf::Event::LostFocus) {
	// 	gk::AudioPlayer::pauseMusic();
	// }
}

