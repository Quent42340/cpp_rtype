/*
 * =====================================================================================
 *
 *       Filename:  Server.cpp
 *
 *    Description:
 *
 *        Created:  23/01/2018 14:48:07
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Server.hpp"
#include "ServerInfo.hpp"
#include "TestEntityFactory.hpp"

void Server::init() {
	Network::setInstance(m_network);

	m_network.init(4242);

	if (m_tcpListener.listen(4243) != sf::Socket::Done)
		throw EXCEPTION("Network error: Listen failed");

	m_tcpListener.setBlocking(false);

	m_selector.add(m_tcpListener);
}

void Server::handleKeyState() {
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
			Client *client = ServerInfo::getInstance().getClient(clientId);
			if (client)
				client->inputHandler.setKeyPressed(keyCode, true);
		}
		else if (command == NetworkCommand::KeyReleased) {
			u32 keyCode;
			packet >> keyCode;
			Client *client = ServerInfo::getInstance().getClient(clientId);
			if (client)
				client->inputHandler.setKeyPressed(keyCode, false);
		}
	}
}

void Server::handleGameEvents(Scene &scene) {
	if (m_selector.wait(sf::milliseconds(10))) {
		if (!m_hasGameStarted && m_selector.isReady(m_tcpListener)) {
			std::shared_ptr<sf::TcpSocket> clientSocket = std::make_shared<sf::TcpSocket>();
			if (m_tcpListener.accept(*clientSocket) == sf::Socket::Done) {
				sf::Packet packet;
				clientSocket->receive(packet);

				NetworkCommand command;
				packet >> command;
				if (command != NetworkCommand::ClientConnect)
					throw EXCEPTION("Network error: Expected 'ClientConnect' packet.");
				u16 port;
				packet >> port;

				Client &client = ServerInfo::getInstance().addClient(port, clientSocket);
				scene.addObject(TestEntityFactory::create(20, 50, client.id));
				m_selector.add(*client.tcpSocket);

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
			bool areAllClientsReady = true;
			for (size_t i = 0 ; i < ServerInfo::getInstance().clients().size() ; ++i) {
				Client &client = ServerInfo::getInstance().clients()[i];
				if (m_selector.isReady(*client.tcpSocket)) {
					sf::Packet packet;
					if (client.tcpSocket->receive(packet) == sf::Socket::Done) {
						NetworkCommand command;
						packet >> command;

						if (command == NetworkCommand::ClientDisconnect) {
							sf::Packet packet;
							packet << NetworkCommand::EntityDie << "Player" + std::to_string(client.id);
							for (Client &client : ServerInfo::getInstance().clients()) {
								client.tcpSocket->send(packet);
							}

							ServerInfo::getInstance().removeClient(client.id);
							m_selector.remove(*client.tcpSocket);

							if (ServerInfo::getInstance().clients().size() == 0) {
								m_tcpListener.close();
								m_isRunning = false;
							}
						}
						else if (command == NetworkCommand::ClientReady) {
							client.isReady = true;
						}
					}
				}

				if (!client.isReady)
					areAllClientsReady = false;
			}

			if (areAllClientsReady) {
				sf::Packet packet;
				packet << NetworkCommand::GameStart;
				for (Client &client : ServerInfo::getInstance().clients()) {
					client.tcpSocket->send(packet);
				}

				m_hasGameStarted = true;
			}
		}
	}
}

