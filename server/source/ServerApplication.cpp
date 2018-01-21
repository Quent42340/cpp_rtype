/*
 * =====================================================================================
 *
 *       Filename:  ServerApplication.cpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 00:22:52
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <SFML/Window/Keyboard.hpp>

#include "GamePad.hpp"
#include "ServerApplication.hpp"
#include "TestEntityFactory.hpp"

ServerApplication::ServerApplication() {
	std::srand(std::time(nullptr));

	GamePad::init(m_inputHandler);

	m_socket.bind(4242);
	m_socket.setBlocking(false);

	m_scene.addObject(TestEntityFactory::createServer(30, 30));
}

void ServerApplication::handleNetworkEvents() {
	sf::Packet packet;
	sf::IpAddress senderAddress;
	u16 senderPort;
	if (m_socket.receive(packet, senderAddress, senderPort) == sf::Socket::Status::Done) {
		std::string type;
		packet >> type;
		std::cout << "Message of type '" << type << "' received from: " << senderAddress << ":" << senderPort << std::endl;

		if (type == "KeyPressed") {
			u32 keyCode;
			packet >> keyCode;
			m_inputHandler.setKeyPressed(keyCode, true);
		}
		else if (type == "KeyReleased") {
			u32 keyCode;
			packet >> keyCode;
			m_inputHandler.setKeyPressed(keyCode, false);
		}
		else if (type == "ClientClose") {
			m_isRunning = false;
		}
		else if (type == "EntityMove") {
			std::string entityName;
			sf::Vector2f pos;
			// float speed;
			packet >> entityName >> pos.x >> pos.y; // >> speed;

			// std::cout << "Entity '" << entityName << "' moved with velocity (" << velocity.x << ";" << velocity.y << ") at " << speed << " speed." << std::endl;
		}
	}
}

void ServerApplication::run() {
	while (m_isRunning) {
		m_clock.updateGame([&] {
			handleNetworkEvents();

			m_scene.update();
		});

		m_clock.waitForNextFrame();
	}
}

