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
#include "ServerInfo.hpp"

Network *Network::s_instance = nullptr;

void Network::init(u16 udpPort) {
	if (m_socket.bind(udpPort) != sf::Socket::Done)
		throw EXCEPTION("Network error: Bind failed");

	m_socket.setBlocking(false);
}

void Network::connect(sf::IpAddress serverAddress, u16 serverPort) {
	m_tcpSocket.reset(new sf::TcpSocket);
	if (serverAddress.toInteger() == 0 || m_tcpSocket->connect(serverAddress, serverPort, sf::seconds(5)) != sf::Socket::Done)
		throw EXCEPTION("Network error: Unable to connect to server", serverAddress.toString() + ":" + std::to_string(serverPort));

	if (m_socket.bind(0) != sf::Socket::Done)
		throw EXCEPTION("Network error: Bind failed");

	sf::Packet packet;
	packet << NetworkCommand::ClientConnect << m_socket.getLocalPort();
	m_tcpSocket->send(packet);

	sf::Packet answer;
	m_tcpSocket->receive(answer);

	NetworkCommand command;
	answer >> command;
	if (command != NetworkCommand::ClientConnect)
		throw EXCEPTION("Network error: Expected 'ClientConnect' packet.");
	answer >> m_clientId;

	m_tcpSocket->setBlocking(false);
	m_socket.setBlocking(false);
}

std::string Network::commandToString(NetworkCommand command) {
	std::map<NetworkCommand, std::string> commandNames = {
		{NetworkCommand::ClientConnect,    "ClientConnect"},
		{NetworkCommand::ClientReady,      "ClientReady"},
		{NetworkCommand::ClientDisconnect, "ClientDisconnect"},
		{NetworkCommand::GameStart,        "GameStart"},
		{NetworkCommand::GameWin,          "GameWin"},
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

