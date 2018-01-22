/*
 * =====================================================================================
 *
 *       Filename:  Network.cpp
 *
 *    Description:
 *
 *        Created:  22/01/2018 14:12:53
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Exception.hpp"
#include "Network.hpp"

Network *Network::s_instance = nullptr;

Network::Network(u16 udpPort) {
	if (m_tcpListener.listen(udpPort + 1) != sf::Socket::Done)
		throw EXCEPTION("Network error: Listen failed");

	if (m_tcpListener.accept(m_tcpSocket) != sf::Socket::Done)
		throw EXCEPTION("Network error: Accept failed");

	if (m_socket.bind(udpPort) != sf::Socket::Done)
		throw EXCEPTION("Network error: Bind failed");

	m_tcpSocket.setBlocking(false);
	m_socket.setBlocking(false);
}

void Network::connect(sf::IpAddress serverAddress, u16 serverPort) {
	if (m_tcpSocket.connect(serverAddress, serverPort) != sf::Socket::Done)
		throw EXCEPTION("Network error: Unable to connect to server");

	if (m_socket.bind(0) != sf::Socket::Done)
		throw EXCEPTION("Network error: Bind failed");

	m_tcpSocket.setBlocking(false);
	m_socket.setBlocking(false);
}

std::string Network::commandToString(NetworkCommand command) {
	std::map<NetworkCommand, std::string> commandNames = {
		{NetworkCommand::ClientConnect,    "ClientConnect"},
		{NetworkCommand::ClientDisconnect, "ClientDisconnect"},
		{NetworkCommand::KeyPressed,       "KeyPressed"},
		{NetworkCommand::KeyReleased,      "KeyReleased"},
		{NetworkCommand::EntityMove,       "EntityMove"},
		{NetworkCommand::EntityDie,        "EntityDie"},
		{NetworkCommand::EntitySpawn,      "EntitySpawn"},
	};
	return commandNames[command];
}

sf::Packet &operator<<(sf::Packet &packet, NetworkCommand command) {
	return packet << static_cast<u16>(command);
}

sf::Packet &operator>>(sf::Packet &packet, NetworkCommand &command) {
	u16 tmp;
	packet >> tmp;
	command = static_cast<NetworkCommand>(tmp);
	return packet;
}

