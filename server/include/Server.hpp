/*
 * =====================================================================================
 *
 *       Filename:  Server.hpp
 *
 *    Description:
 *
 *        Created:  23/01/2018 14:47:14
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "Network.hpp"
#include "Scene.hpp"

class Server {
	public:
		void init();

		void handleKeyState();

		void handleGameEvents(Scene &scene);

		bool isRunning() const { return m_isRunning; }
		bool hasGameStarted() const { return m_hasGameStarted; }

	private:
		bool m_isRunning = true;
		bool m_hasGameStarted = false;

		Network m_network;

		sf::TcpListener m_tcpListener;
		sf::SocketSelector m_selector;
};

#endif // SERVER_HPP_
