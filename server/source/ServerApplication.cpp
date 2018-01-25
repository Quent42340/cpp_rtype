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
#include "EnemyInfoLoader.hpp"
#include "ServerApplication.hpp"
#include "ServerInfo.hpp"

void ServerApplication::init() {
	std::srand(std::time(nullptr));

	ResourceHandler::setInstance(m_resourceHandler);

	m_resourceHandler.loadConfigFile<EnemyInfoLoader>("data/config/enemies.xml");

	m_server.init();
}

int ServerApplication::run() {
	int returnValue = 0;
	try {
		init();
		mainLoop();
	}
	catch(const Exception &e) {
		std::cerr << "Fatal error " << e.what() << std::endl;
		returnValue = 1;
	}
	catch(const std::exception &e) {
		std::cerr << "Exception caught: " << e.what() << std::endl;
		returnValue = 1;
	}
	catch(...) {
		std::cerr << "Fatal error: Unknown error." << std::endl;
		return 1;
	}

	return returnValue;
}

void ServerApplication::mainLoop() {
	while (m_server.isRunning()) {
		m_server.handleGameEvents(m_scene);

		if (m_server.hasGameStarted()) {
			m_server.handleKeyState();

			m_clock.updateGame([&] {
				if (ServerInfo::getInstance().clients().size() > 0)
					m_spawnController.update(m_scene);

				m_scene.update();
			});

			m_clock.waitForNextFrame();
		}
	}
}

