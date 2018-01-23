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
#include <SFML/Window/Keyboard.hpp>

#include "Config.hpp"
#include "GamePad.hpp"
#include "ServerApplication.hpp"
#include "TestEnemyFactory.hpp"

void ServerApplication::init() {
	std::srand(std::time(nullptr));

	m_spawnTimer.start();
	m_server.init();
}

void ServerApplication::update() {
	if (m_spawnTimer.time() > 2000) {
		m_spawnTimer.reset();
		m_spawnTimer.start();

		m_scene.addObject(TestEnemyFactory::create({Config::screenWidth + 20, static_cast<float>(std::rand() % (Config::screenHeight - 40))}));
	}

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

	Network::getInstance().tcpListener().close();

	return returnValue;
}

void ServerApplication::mainLoop() {
	while (m_server.isRunning()) {
		m_server.handleKeyState();
		m_server.handleGameEvents(m_scene);

		m_clock.updateGame([&] {
			update();
			m_scene.update();
		});

		m_clock.waitForNextFrame();
	}
}

