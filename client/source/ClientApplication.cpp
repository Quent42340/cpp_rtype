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
#include "ClientApplication.hpp"
#include "GamePad.hpp"
#include "Mouse.hpp"
#include "NetworkCommandHandler.hpp"
#include "TextureLoader.hpp"

#include "GameState.hpp"

void ClientApplication::init() {
	std::srand(std::time(nullptr));

	m_window.create(sf::VideoMode(screenWidth, screenHeight), "R-Type", sf::Style::Close);
	m_window.setKeyRepeatEnabled(false);

	Mouse::setWindow(m_window);

	ApplicationStateStack::setInstance(m_stateStack);
	Network::setInstance(m_network);
	ResourceHandler::setInstance(m_resourceHandler);

	m_resourceHandler.loadConfigFile<TextureLoader>("data/config/textures.xml");

	GamePad::init(m_keyboardHandler);

	ApplicationStateStack::getInstance().push<GameState>();

	NetworkCommandHandler::connect();
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

		m_stateStack.top().onEvent(event);

		m_keyboardHandler.updateState(event);

		if (event.type == sf::Event::KeyPressed) {
			NetworkCommandHandler::sendKey(event.key.code, true);
		}
		else if (event.type == sf::Event::KeyReleased) {
			NetworkCommandHandler::sendKey(event.key.code, false);
		}
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

	return 0;
}

void ClientApplication::mainLoop() {
	while(m_window.isOpen()) {
		handleEvents();

		m_clock.updateGame([&] {
			if (m_stateStack.size() == 0)
				m_window.close();
			m_stateStack.top().update();
		});

		m_clock.drawGame([&] {
			m_window.clear();

			m_window.draw(ApplicationStateStack::getInstance().top());

			m_window.display();
		});
	}
}

