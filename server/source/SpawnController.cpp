/*
 * =====================================================================================
 *
 *       Filename:  SpawnController.cpp
 *
 *    Description:
 *
 *        Created:  23/01/2018 17:45:28
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "BossFactory.hpp"
#include "Config.hpp"
#include "GenericEnemyFactory.hpp"
#include "SpawnController.hpp"
#include "ResourceHandler.hpp"

SpawnController::SpawnController() {
	m_spawnTimer.start();
}

void SpawnController::update(Server &server, Scene &scene) {
	if ((!m_hasBoss && m_spawnTimer.time() > 2150 - 150 * server.info().clients().size())
	 || (m_hasBoss && m_spawnTimer.time() > 3000 - 200 * server.info().clients().size())) {
		m_spawnTimer.reset();
		m_spawnTimer.start();

		if (!m_bossSpawnTimer.isStarted()) {
			m_bossSpawnTimer.reset();
			m_bossSpawnTimer.start();
		}

		sf::Vector2f pos{Config::screenWidth + 20, static_cast<float>(std::rand() % (Config::screenHeight - 40))};
		EnemyInfo &info = ResourceHandler::getInstance().get<EnemyInfo>("info-enemy" + std::to_string(rand() % 3 + 1));
		scene.addObject(GenericEnemyFactory::create(info, pos));
	}

	if (!m_hasBoss && m_bossSpawnTimer.time() > 60000) {
	// if (!m_hasBoss && m_bossSpawnTimer.time() > 10000) {
		scene.addObject(BossFactory::create());
		m_hasBoss = true;
	}
}

