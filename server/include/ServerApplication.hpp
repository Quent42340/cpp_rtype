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
#include "Server.hpp"
#include "Scene.hpp"
#include "Timer.hpp"

class ServerApplication {
	public:
		void init();

		void update();

		int run();
		void mainLoop();

	private:
		GameClock m_clock;

		Scene m_scene;

		Server m_server;

		Timer m_spawnTimer;
};

#endif // SERVERAPPLICATION_HPP_
