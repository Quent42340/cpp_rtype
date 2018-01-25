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

std::string Network::commandToString(NetworkCommand command) {
	std::map<NetworkCommand, std::string> commandNames = {
		{NetworkCommand::ClientConnect,    "ClientConnect"},
		{NetworkCommand::ClientReady,      "ClientReady"},
		{NetworkCommand::ClientDisconnect, "ClientDisconnect"},
		{NetworkCommand::GameStart,        "GameStart"},
		{NetworkCommand::GameWin,          "GameWin"},
		{NetworkCommand::KeyPressed,       "KeyPressed"},
		{NetworkCommand::KeyReleased,      "KeyReleased"},
		{NetworkCommand::EntityState,      "EntityState"},
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

