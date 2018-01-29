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
#include "SpawnController.hpp"
#include "ResourceHandler.hpp"

class ServerApplication {
	public:
		ServerApplication(Server &server) : m_server(server) {}

		void init();

		void run();
		void mainLoop();

	private:
		GameClock m_clock;

		Scene m_scene;
		SpawnController m_spawnController;

		Server &m_server;

		ResourceHandler m_resourceHandler;
};

#endif // SERVERAPPLICATION_HPP_
