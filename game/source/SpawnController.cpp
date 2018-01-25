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
#include "SpawnController.hpp"
#include "TestEnemyFactory.hpp"

SpawnController::SpawnController() {
	m_spawnTimer.start();
}

void SpawnController::update(Scene &scene) {
	if (!m_hasBoss && m_spawnTimer.time() > 2000) {
		m_spawnTimer.reset();
		m_spawnTimer.start();

		if (!m_bossSpawnTimer.isStarted()) {
			m_bossSpawnTimer.reset();
			m_bossSpawnTimer.start();
		}

		scene.addObject(TestEnemyFactory::create({Config::screenWidth + 20, static_cast<float>(std::rand() % (Config::screenHeight - 40))}));
	}

	if (!m_hasBoss && m_bossSpawnTimer.time() > 60000) {
	// if (!m_hasBoss && m_bossSpawnTimer.time() > 2000) {
		scene.addObject(BossFactory::create());
		m_hasBoss = true;
	}
}

