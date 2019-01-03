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

namespace Network {
	enum class Command {
		// Client commands
		ClientConnect,     // <TCP> [NetworkCommand][u16 udp port]
		ClientOk,          // <TCP> [NetworkCommand][u16 client id]
		ClientRefused,     // <TCP> [NetworkCommand]
		ClientReady,       // <TCP> [NetworkCommand][u16 client id]
		ClientDisconnect,  // <TCP> [NetworkCommand]

		// Game commands
		GameStart,         // <TCP> [NetworkCommand]
		GameWin,           // <TCP> [NetworkCommand]

		// Input commands
		KeyState,          // <UDP> [NetworkCommand][u32 timestamp][u16 client id][u32 keycode][bool isPressed]...

		// Game commands
		EntityState,       // <UDP> [NetworkCommand][u32 timestamp][std::string name][float x][float y][float vx][float vy]
		EntityDie,         // <TCP> [NetworkCommand][std::string name][float x][float y]
		EntitySpawn        // <TCP> [NetworkCommand][std::string name][std::string type][float x][float y][std::string texture]
	};

	std::string commandToString(Command command);
}

sf::Packet &operator<<(sf::Packet &packet, Network::Command command);
sf::Packet &operator>>(sf::Packet &packet, Network::Command &command);

#endif // NETWORK_HPP_
