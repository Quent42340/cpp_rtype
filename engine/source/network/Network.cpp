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
#include "Network.hpp"

Network *Network::s_instance = nullptr;

Network::Network(u16 port, bool isBlocking) {
	m_socket.bind(port);
	m_socket.setBlocking(isBlocking);
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

