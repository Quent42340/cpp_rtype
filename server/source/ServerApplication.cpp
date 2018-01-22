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
#include "ServerInfo.hpp"
#include "TestEnemyFactory.hpp"
#include "TestEntityFactory.hpp"

ServerApplication::ServerApplication() : m_network(4242, false) {
	std::srand(std::time(nullptr));

	Network::setInstance(m_network);

	// m_clock.setTimestep(50);

	m_spawnTimer.start();
}

void ServerApplication::handleNetworkEvents() {
	if (m_spawnTimer.time() > 2000) {
		m_spawnTimer.reset();
		m_spawnTimer.start();

		m_scene.addObject(TestEnemyFactory::create({Application::screenWidth + 20, static_cast<float>(std::rand() % (Application::screenHeight - 40))}));
	}

	sf::Packet packet;
	sf::IpAddress senderAddress;
	u16 senderPort;
	while (m_network.socket().receive(packet, senderAddress, senderPort) == sf::Socket::Status::Done) {
		NetworkCommand command;
		packet >> command;
		// std::cout << "Message of type '" << Network::commandToString(command) << "' received from: " << senderAddress << ":" << senderPort << std::endl;

		if (command == NetworkCommand::KeyPressed) {
			u32 keyCode;
			packet >> keyCode;
			ServerInfo::getInstance().getClient(senderPort).inputHandler.setKeyPressed(keyCode, true);
		}
		else if (command == NetworkCommand::KeyReleased) {
			u32 keyCode;
			packet >> keyCode;
			ServerInfo::getInstance().getClient(senderPort).inputHandler.setKeyPressed(keyCode, false);
		}
		else if (command == NetworkCommand::ClientConnect) {
			ServerInfo::getInstance().addClient(senderPort);
			m_scene.addObject(TestEntityFactory::create(20, 50, senderPort));
		}
		else if (command == NetworkCommand::ClientDisconnect) {
			ServerInfo::getInstance().removeClient(senderPort);
			if (ServerInfo::getInstance().clients().size() == 0)
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
		handleNetworkEvents();

		m_clock.updateGame([&] {
			m_scene.update();
		});

		m_clock.waitForNextFrame();
	}
}

