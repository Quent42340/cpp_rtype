/*
 * =====================================================================================
 *
 *       Filename:  TestEnemyFactory.hpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 05:37:26
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef TESTENEMYFACTORY_HPP_
#define TESTENEMYFACTORY_HPP_

#include "CollisionComponent.hpp"
#include "SceneObject.hpp"

class TestEnemyFactory {
	public:
		static SceneObject create(const sf::Vector2f &pos);

	private:
		static void enemyCollisionAction(SceneObject &enemy, SceneObject &object, bool inCollision);

		static bool checkOutOfMap(const SceneObject &object);
};

#endif // TESTENEMYFACTORY_HPP_
