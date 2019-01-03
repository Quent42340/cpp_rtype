/*
 * =====================================================================================
 *
 *       Filename:  GenericEnemyFactory.hpp
 *
 *    Description:
 *
 *        Created:  25/01/2018 11:17:24
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GENERICENEMYFACTORY_HPP_
#define GENERICENEMYFACTORY_HPP_

#include <gk/core/Vector2.hpp>
#include <gk/scene/SceneObject.hpp>

#include "EnemyInfo.hpp"

class GenericEnemyFactory {
	public:
		static gk::SceneObject create(const EnemyInfo &info, const gk::Vector2f &pos);

	private:
		static void enemyCollisionAction(gk::SceneObject &enemy, gk::SceneObject &object, bool inCollision);

		static bool checkOutOfMap(const gk::SceneObject &object);
};

#endif // GENERICENEMYFACTORY_HPP_
