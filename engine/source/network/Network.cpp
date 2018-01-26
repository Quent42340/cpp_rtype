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
#include <map>

#include "Network.hpp"

std::string Network::commandToString(Network::Command command) {
	std::map<Network::Command, std::string> commandNames = {
		{Network::Command::ClientConnect,    "ClientConnect"},
		{Network::Command::ClientReady,      "ClientReady"},
		{Network::Command::ClientDisconnect, "ClientDisconnect"},
		{Network::Command::GameStart,        "GameStart"},
		{Network::Command::GameWin,          "GameWin"},
		{Network::Command::KeyPressed,       "KeyPressed"},
		{Network::Command::KeyReleased,      "KeyReleased"},
		{Network::Command::EntityState,      "EntityState"},
		{Network::Command::EntityDie,        "EntityDie"},
		{Network::Command::EntitySpawn,      "EntitySpawn"},
	};
	return commandNames[command];
}

sf::Packet &operator<<(sf::Packet &packet, Network::Command command) {
	return packet << static_cast<u16>(command);
}

sf::Packet &operator>>(sf::Packet &packet, Network::Command &command) {
	u16 tmp;
	packet >> tmp;
	command = static_cast<Network::Command>(tmp);
	return packet;
}

