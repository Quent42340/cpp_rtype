/*
 * =====================================================================================
 *
 *       Filename:  SpawnController.hpp
 *
 *    Description:
 *
 *        Created:  23/01/2018 17:45:08
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SPAWNCONTROLLER_HPP_
#define SPAWNCONTROLLER_HPP_

#include <gk/core/Timer.hpp>
#include <gk/scene/Scene.hpp>

#include "Server.hpp"

class SpawnController {
	public:
		SpawnController();

		void update(Server &server, gk::Scene &scene);

	private:
		gk::Timer m_spawnTimer;
		gk::Timer m_bossSpawnTimer;

		bool m_hasBoss = false;
};

#endif // SPAWNCONTROLLER_HPP_
