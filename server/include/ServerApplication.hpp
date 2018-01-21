/*
 * =====================================================================================
 *
 *       Filename:  ServerApplication.hpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 00:22:13
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SERVERAPPLICATION_HPP_
#define SERVERAPPLICATION_HPP_

#include <SFML/Network.hpp>

#include "GameClock.hpp"
#include "NetworkInputHandler.hpp"
#include "Scene.hpp"

class ServerApplication {
	public:
		ServerApplication();

		void handleNetworkEvents();

		void run();

	private:
		bool m_isRunning = true;

		GameClock m_clock;

		NetworkInputHandler m_inputHandler;

		sf::UdpSocket m_socket;

		Scene m_scene;
};

#endif // SERVERAPPLICATION_HPP_
