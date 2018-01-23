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
			ServerInfo::getInstance().getClient(clientId).inputHandler.setKeyPressed(keyCode, true);
		}
		else if (command == NetworkCommand::KeyReleased) {
			u32 keyCode;
			packet >> keyCode;
			ServerInfo::getInstance().getClient(clientId).inputHandler.setKeyPressed(keyCode, false);
		}
	}
}

void Server::handleGameEvents(Scene &scene) {
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
				scene.addObject(TestEntityFactory::create(20, 50, client.id));
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

