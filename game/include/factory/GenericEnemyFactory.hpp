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

#include "EnemyInfo.hpp"
#include "SceneObject.hpp"

class GenericEnemyFactory {
	public:
		static SceneObject create(const EnemyInfo &info, const gk::Vector2f &pos);

	private:
		static void enemyCollisionAction(SceneObject &enemy, SceneObject &object, bool inCollision);

		static bool checkOutOfMap(const SceneObject &object);
};

#endif // GENERICENEMYFACTORY_HPP_
