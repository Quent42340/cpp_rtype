/*
 * =====================================================================================
 *
 *       Filename:  Network.hpp
 *
 *    Description:
 *
 *        Created:  22/01/2018 14:11:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <SFML/Network/Packet.hpp>

#include "Scene.hpp"

namespace Network {
	enum class Command {
		// Client commands
		ClientConnect,     // [NetworkCommand][u16 udp port/client id]
		ClientReady,       // [NetworkCommand][u16 client id]
		ClientDisconnect,  // [NetworkCommand]

		// Game commands
		GameStart,         // [NetworkCommand]
		GameWin,           // [NetworkCommand]

		// Input commands
		KeyPressed,        // [NetworkCommand][u32 sfml keycode]
		KeyReleased,       // [NetworkCommand][u32 sfml keycode]

		// Game commands
		EntityState,       // [NetworkCommand][u32 timestamp][std::string name][float x][float y][float vx][float vy]
		EntityDie,         // [NetworkCommand][std::string name][float x][float y]
		EntitySpawn        // [NetworkCommand][std::string name][std::string type][float x][float y][std::string texture]
	};

	std::string commandToString(Command command);
}

sf::Packet &operator<<(sf::Packet &packet, Network::Command command);
sf::Packet &operator>>(sf::Packet &packet, Network::Command &command);

#endif // NETWORK_HPP_
