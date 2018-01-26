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
#include <SFML/Audio/Music.hpp>

#include "AudioLoader.hpp"
#include "AudioPlayer.hpp"
#include "ClientApplication.hpp"
#include "Config.hpp"
#include "GamePad.hpp"
#include "Mouse.hpp"
#include "SpriteLoader.hpp"
#include "TextureLoader.hpp"

#include "GameState.hpp"
#include "TitleScreenState.hpp"

ClientApplication::ClientApplication(int argc, char **argv) {
	if (argc > 1 && argv[1] == std::string("--no-sound"))
		AudioPlayer::setMuteState(true);
}

void ClientApplication::init() {
	std::srand(std::time(nullptr));

	m_window.create(sf::VideoMode(Config::screenWidth, Config::screenHeight), "R-Type", sf::Style::Close);

	Mouse::setWindow(m_window);

	ApplicationStateStack::setInstance(m_stateStack);
	ResourceHandler::setInstance(m_resourceHandler);

	m_resourceHandler.loadConfigFile<AudioLoader>("data/config/audio.xml");
	m_resourceHandler.loadConfigFile<TextureLoader>("data/config/textures.xml");
	m_resourceHandler.loadConfigFile<SpriteLoader>("data/config/sprites.xml");
	m_resourceHandler.add<sf::Font>("font-default").loadFromFile("fonts/arial.ttf");
	m_resourceHandler.add<sf::Font>("font-pdark").loadFromFile("fonts/pdark.ttf");

	GamePad::init(m_keyboardHandler);

	ApplicationStateStack::getInstance().push<TitleScreenState>();
}

void ClientApplication::handleEvents() {
	m_keyboardHandler.resetState();

	sf::Event event;
	while(m_window.pollEvent(event)) {
		if (event.type == sf::Event::GainedFocus) {
			AudioPlayer::resumeMusic();
		}
		else if (event.type == sf::Event::LostFocus) {
			AudioPlayer::pauseMusic();
		}

		m_stateStack.top().onEvent(event);

		m_keyboardHandler.updateState(event);
	}
}

int ClientApplication::run() {
	try {
		init();
		mainLoop();
	}
	catch(const Exception &e) {
		std::cerr << "Fatal error " << e.what() << std::endl;
		return 1;
	}
	catch(const std::exception &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		return 1;
	}
	catch(...) {
		std::cerr << "Fatal error: Unknown error." << std::endl;
		return 1;
	}

	return 0;
}

void ClientApplication::mainLoop() {
	while(m_window.isOpen() && m_stateStack.size()) {
		handleEvents();

		m_clock.updateGame([&] {
			if (m_stateStack.size() > 0)
				m_stateStack.top().update();

			m_stateStack.clearDeletedStates();
		});

		m_clock.drawGame([&] {
			m_window.clear();

			if (m_stateStack.size() > 0)
				m_window.draw(m_stateStack.top());

			m_window.display();
		});
	}
}

