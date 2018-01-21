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
#include "TextureLoader.hpp"

#include "GameState.hpp"

bool ClientApplication::quit = false;

void ClientApplication::init() {
	std::srand(std::time(nullptr));

	m_window.create(sf::VideoMode(screenWidth, screenHeight), "R-Type", sf::Style::Close);
	m_window.setKeyRepeatEnabled(false);

	m_socket.bind(4243);

	Mouse::setWindow(m_window);

	ApplicationStateStack::setInstance(m_stateStack);
	ResourceHandler::setInstance(m_resourceHandler);

	m_resourceHandler.loadConfigFile<TextureLoader>("data/config/textures.xml");

	GamePad::init(m_keyboardHandler);

	ApplicationStateStack::getInstance().push<GameState>();
}

void ClientApplication::handleEvents() {
	m_keyboardHandler.resetState();

	sf::Event event;
	while(m_window.pollEvent(event)) {
		if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		 || event.type == sf::Event::Closed) {
			m_window.close();
		}

		m_keyboardHandler.updateState(event);

		if (event.type == sf::Event::KeyPressed) {
			sf::Packet packet;
			packet << "Key pressed! Code: " << event.key.code;
			m_socket.send(packet, sf::IpAddress::Broadcast, 4242);
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
			if(quit) m_window.close();

			ApplicationStateStack::getInstance().top().update();
		});

		m_clock.drawGame([&] {
			m_window.clear();

			m_window.draw(ApplicationStateStack::getInstance().top());

			m_window.display();
		});
	}
}

