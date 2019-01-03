/*
 * =====================================================================================
 *
 *       Filename:  ServerApplication.cpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 00:22:52
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/scene/controller/BehaviourController.hpp>
#include <gk/scene/controller/LifetimeController.hpp>
#include <gk/scene/controller/MovementController.hpp>

#include "EnemyInfoLoader.hpp"
#include "GamePadController.hpp"
#include "NetworkController.hpp"
#include "ServerApplication.hpp"

void ServerApplication::init() {
	std::srand(std::time(nullptr));

	gk::ResourceHandler::setInstance(m_resourceHandler);

	m_resourceHandler.loadConfigFile<EnemyInfoLoader>("resources/config/enemies.xml");

	// m_server.init();

	m_scene.addController<gk::LifetimeController>();
	m_scene.addController<GamePadController>(m_server.info());
	m_scene.addController<gk::BehaviourController>();
	m_scene.addController<gk::MovementController>();
	m_scene.addController<NetworkController>(m_server.info(), m_server.udpSocket());
}

void ServerApplication::run() {
	init();
	mainLoop();
}

void ServerApplication::mainLoop() {
	while (m_server.isRunning()) {
		m_server.handleGameEvents(m_scene);

		if (m_server.hasGameStarted()) {
			m_server.handleKeyState();

			m_clock.updateGame([&] {
				m_spawnController.update(m_server, m_scene);

				m_scene.update();
			});

			m_clock.waitForNextFrame();
		}
	}
}

