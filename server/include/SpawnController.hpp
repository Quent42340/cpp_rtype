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

#include "Scene.hpp"
#include "Server.hpp"
#include "Timer.hpp"

class SpawnController {
	public:
		SpawnController();

		void update(Server &server, Scene &scene);

	private:
		Timer m_spawnTimer;
		Timer m_bossSpawnTimer;
		bool m_hasBoss = false;
};

#endif // SPAWNCONTROLLER_HPP_
