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

	private:
		Network m_network;

		bool m_isRunning = true;
};

#endif // SERVER_HPP_
