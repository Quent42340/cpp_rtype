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

#include "Config.hpp"
#include "GamePad.hpp"
#include "ServerApplication.hpp"
#include "ServerInfo.hpp"
#include "TestEnemyFactory.hpp"
#include "TestEntityFactory.hpp"

ServerApplication::ServerApplication() {
	std::srand(std::time(nullptr));

	Network::setInstance(m_network);

	// m_clock.setTimestep(50);

	m_network.init(4242);

	m_spawnTimer.start();
}

void ServerApplication::handleNetworkEvents() {
	if (m_spawnTimer.time() > 2000) {
		m_spawnTimer.reset();
		m_spawnTimer.start();

		m_scene.addObject(TestEnemyFactory::create({Config::screenWidth + 20, static_cast<float>(std::rand() % (Config::screenHeight - 40))}));
	}

	sf::Packet packet;
	sf::IpAddress senderAddress;
	u16 senderPort;
	while (m_network.socket().receive(packet, senderAddress, senderPort) == sf::Socket::Status::Done) {
		NetworkCommand command;
		u16 clientId;
		packet >> command >> clientId;
		// std::cout << "Message of type '" << Network::commandToString(command) << "' received from: " << senderAddress << ":" << senderPort << std::endl;

		if (command == NetworkCommand::KeyPressed) {
			u32 keyCode;
			packet >> keyCode;
			ServerInfo::getInstance().getClient(clientId).inputHandler.setKeyPressed(keyCode, true);
		}
		else if (command == NetworkCommand::KeyReleased) {
			u32 keyCode;
			packet >> keyCode;
			ServerInfo::getInstance().getClient(clientId).inputHandler.setKeyPressed(keyCode, false);
		}
	}

	if (m_network.selector().wait(sf::milliseconds(10))) {
		if (m_network.selector().isReady(m_network.tcpListener())) {
			std::shared_ptr<sf::TcpSocket> clientSocket = std::make_shared<sf::TcpSocket>();
			if (m_network.tcpListener().accept(*clientSocket) == sf::Socket::Done) {
				sf::Packet packet;
				clientSocket->receive(packet);

				NetworkCommand command;
				packet >> command;
				if (command != NetworkCommand::ClientConnect)
					throw EXCEPTION("Network error: Expected 'ClientConnect' packet.");
				u16 port;
				packet >> port;

				Client &client = ServerInfo::getInstance().addClient(port, clientSocket);
				m_scene.addObject(TestEntityFactory::create(20, 50, client.id));
				m_network.selector().add(*client.tcpSocket);

				sf::Packet outPacket;
				outPacket << NetworkCommand::ClientConnect << client.id;
				client.tcpSocket->send(outPacket);
				client.tcpSocket->setBlocking(false);
			}
			else {
				std::cerr << "Warning: Connection accept failed." << std::endl;
			}
		}
		else {
			for (Client &client : ServerInfo::getInstance().clients()) {
				if (m_network.selector().isReady(*client.tcpSocket)) {
					sf::Packet packet;
					if (client.tcpSocket->receive(packet) == sf::Socket::Done) {
						NetworkCommand command;
						packet >> command;

						if (command == NetworkCommand::ClientDisconnect) {
							ServerInfo::getInstance().removeClient(client.id);
							if (ServerInfo::getInstance().clients().size() == 0)
								m_isRunning = false;
						}
					}
				}
			}
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

