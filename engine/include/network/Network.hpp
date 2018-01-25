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

#include <SFML/Network.hpp>

#include "Scene.hpp"

enum class NetworkCommand {
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
	EntityState,       // [NetworkCommand][std::string name][float x][float y][float vx][float vy]
	EntityDie,         // [NetworkCommand][std::string name][float x][float y]
	EntitySpawn        // [NetworkCommand][std::string name][std::string type][float x][float y][std::string texture]
};

class Network {
	public:
		void init(u16 udpPort);

		sf::UdpSocket &socket() { return m_socket; }

		static std::string commandToString(NetworkCommand command);

		static void setInstance(Network &instance) { s_instance = &instance; }
		static Network &getInstance() { return *s_instance; }

	private:
		static Network *s_instance;

		sf::UdpSocket m_socket;
};

sf::Packet &operator<<(sf::Packet &packet, NetworkCommand command);
sf::Packet &operator>>(sf::Packet &packet, NetworkCommand &command);

#endif // NETWORK_HPP_
