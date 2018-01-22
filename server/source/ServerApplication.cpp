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

#include "Application.hpp"
#include "GamePad.hpp"
#include "ServerApplication.hpp"
#include "TestEnemyFactory.hpp"
#include "TestEntityFactory.hpp"

ServerApplication::ServerApplication() : m_network(4242, false) {
	std::srand(std::time(nullptr));

	GamePad::init(m_inputHandler);

	// m_clock.setTimestep(50);

	Network::setInstance(m_network);

	m_spawnTimer.start();
}

void ServerApplication::handleNetworkEvents() {
	if (m_spawnTimer.time() > 2000) {
		m_spawnTimer.reset();
		m_spawnTimer.start();

		m_scene.addObject(TestEnemyFactory::createServer({Application::screenWidth + 20, static_cast<float>(std::rand() % (Application::screenHeight - 40))}));
	}

	sf::Packet packet;
	sf::IpAddress senderAddress;
	u16 senderPort;
	while (m_network.socket().receive(packet, senderAddress, senderPort) == sf::Socket::Status::Done) {
		NetworkCommand command;
		packet >> command;
		std::cout << "Message of type '" << Network::commandToString(command) << "' received from: " << senderAddress << ":" << senderPort << std::endl;

		if (command == NetworkCommand::KeyPressed) {
			u32 keyCode;
			packet >> keyCode;
			m_inputHandler.setKeyPressed(keyCode, true);
		}
		else if (command == NetworkCommand::KeyReleased) {
			u32 keyCode;
			packet >> keyCode;
			m_inputHandler.setKeyPressed(keyCode, false);
		}
		else if (command == NetworkCommand::ClientConnect) {
			m_scene.addObject(TestEntityFactory::createServer(20, 50));
		}
		else if (command == NetworkCommand::ClientDisconnect) {
			m_isRunning = false;
		}
	}
}

int ServerApplication::run() {
	try {
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

void ServerApplication::mainLoop() {
	while (m_isRunning) {
		m_clock.updateGame([&] {
			handleNetworkEvents();

			m_scene.update();
		});

		m_clock.waitForNextFrame();
	}
}

