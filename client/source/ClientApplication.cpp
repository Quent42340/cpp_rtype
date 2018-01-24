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

#include "AudioPlayer.hpp"
#include "ClientApplication.hpp"
#include "GamePad.hpp"
#include "Mouse.hpp"
#include "NetworkCommandHandler.hpp"
#include "TextureLoader.hpp"

#include "GameState.hpp"
#include "TitleScreenState.hpp"

void ClientApplication::init() {
	std::srand(std::time(nullptr));

	m_window.create(sf::VideoMode(screenWidth, screenHeight), "R-Type", sf::Style::Close);
	// m_window.setKeyRepeatEnabled(false);

	Mouse::setWindow(m_window);

	ApplicationStateStack::setInstance(m_stateStack);
	Network::setInstance(m_network);
	ResourceHandler::setInstance(m_resourceHandler);

	m_resourceHandler.loadConfigFile<TextureLoader>("data/config/textures.xml");
	m_resourceHandler.add<sf::Font>("font-default").loadFromFile("fonts/arial.ttf");
	m_resourceHandler.add<sf::Font>("font-pdark").loadFromFile("fonts/pdark.ttf");
	m_resourceHandler.add<sf::Music>("music-theme").openFromFile("audio/music/theme.ogg");
	m_resourceHandler.add<sf::Music>("music-game").openFromFile("audio/music/game.ogg");
	m_resourceHandler.add<sf::Music>("music-victory").openFromFile("audio/music/victory.ogg");
	m_resourceHandler.add<sf::Music>("music-gameover").openFromFile("audio/music/gameover.ogg");
	m_resourceHandler.add<sf::Music>("sound-button").openFromFile("audio/sound/button.ogg");
	m_resourceHandler.add<sf::Music>("sound-keyboard").openFromFile("audio/sound/keyboard.ogg");

	GamePad::init(m_keyboardHandler);

	// ApplicationStateStack::getInstance().push<GameState>();
	ApplicationStateStack::getInstance().push<TitleScreenState>();
}

void ClientApplication::handleEvents() {
	m_keyboardHandler.resetState();

	sf::Event event;
	while(m_window.pollEvent(event)) {
		if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		 || event.type == sf::Event::Closed) {
			NetworkCommandHandler::disconnect();

			m_window.close();
		}

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
		m_network.tcpSocket().disconnect();
		return 1;
	}
	catch(const std::exception &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		m_network.tcpSocket().disconnect();
		return 1;
	}

	m_network.tcpSocket().disconnect();
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

