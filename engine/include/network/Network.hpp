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
	ClientDisconnect,  // [NetworkCommand]

	// Input commands
	KeyPressed,        // [NetworkCommand][u32 sfml keycode]
	KeyReleased,       // [NetworkCommand][u32 sfml keycode]

	// Game commands
	EntityMove,        // [NetworkCommand][std::string name][float x][float y]
	EntityDie,         // [NetworkCommand][std::string name][float x][float y]
	EntitySpawn        // [NetworkCommand][std::string name][std::string type][float x][float y][std::string texture][u16 frameWidth][u16 frameHeight][u16 initialFrame]
};

class Network {
	public:
		// Server-side
		void init(u16 udpPort);

		// Client-side
		void connect(sf::IpAddress serverAddress, u16 serverPort);

		// template<typename... Args>
		// void send(sf::IpAddress address, u16 port, NetworkCommand command, Args &&...args);

		// Client-side
		sf::TcpSocket &tcpSocket() { return m_tcpSocket; }
		u16 clientId() const { return m_clientId; }

		// Both
		sf::UdpSocket &socket() { return m_socket; }

		static std::string commandToString(NetworkCommand command);

		static void setInstance(Network &instance) { s_instance = &instance; }
		static Network &getInstance() { return *s_instance; }

	private:
		static Network *s_instance;

		// Client-side
		sf::TcpSocket m_tcpSocket;
		u16 m_clientId;

		// Both
		sf::UdpSocket m_socket;
};

sf::Packet &operator<<(sf::Packet &packet, NetworkCommand command);
sf::Packet &operator>>(sf::Packet &packet, NetworkCommand &command);

#endif // NETWORK_HPP_
