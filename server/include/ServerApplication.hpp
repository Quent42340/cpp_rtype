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
#include "Scene.hpp"
#include "Timer.hpp"

class ServerApplication {
	public:
		ServerApplication();

		void handleNetworkEvents();

		int run();
		void mainLoop();

	private:
		bool m_isRunning = true;

		GameClock m_clock;

		Network m_network;

		Scene m_scene;

		Timer m_spawnTimer;
};

#endif // SERVERAPPLICATION_HPP_
