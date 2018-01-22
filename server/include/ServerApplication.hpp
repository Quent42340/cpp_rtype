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

#include "GameClock.hpp"
#include "Network.hpp"
#include "NetworkInputHandler.hpp"
#include "Scene.hpp"

class ServerApplication {
	public:
		ServerApplication();

		void handleNetworkEvents();

		int run();
		void mainLoop();

	private:
		bool m_isRunning = true;

		GameClock m_clock;

		NetworkInputHandler m_inputHandler;

		Network m_network;

		Scene m_scene;
};

#endif // SERVERAPPLICATION_HPP_
