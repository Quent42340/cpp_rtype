/*
 * =====================================================================================
 *
 *       Filename:  Client.hpp
 *
 *    Description:
 *
 *        Created:  25/01/2018 12:26:01
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/UdpSocket.hpp>

#include "ApplicationStateStack.hpp"
#include "Scene.hpp"

class Client {
	public:
		void connect(sf::IpAddress serverAddress, u16 serverPort);
		void disconnect();

		void sendReady();
		void sendKey(u32 key, bool isPressed);

		void update(ApplicationStateStack &stateStack, Scene &scene, bool &hasGameStarted);

		u16 id() const { return m_id; }

	private:
		void handleEntityStateMessage(Scene &scene, sf::Packet &packet);
		bool handleEntityDieMessage(ApplicationStateStack &stateStack, Scene &scene, sf::Packet &packet);
		void handleEntitySpawnMessage(Scene &scene, sf::Packet &packet);

		u16 m_id;

		std::unique_ptr<sf::TcpSocket> m_tcpSocket;

		sf::UdpSocket m_socket;
};

#endif // CLIENT_HPP_
