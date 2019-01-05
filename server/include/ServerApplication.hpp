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

#include <gk/resource/ResourceHandler.hpp>
#include <gk/scene/Scene.hpp>
#include <gk/core/GameClock.hpp>

#include "Server.hpp"
#include "SpawnController.hpp"

class ServerApplication {
	public:
		ServerApplication(Server &server) : m_server(server) {}

		void init();

		void run();
		void mainLoop();

	private:
		gk::GameClock m_clock;

		gk::Scene m_scene;
		SpawnController m_spawnController;

		Server &m_server;

		gk::ResourceHandler m_resourceHandler;
};

#endif // SERVERAPPLICATION_HPP_
