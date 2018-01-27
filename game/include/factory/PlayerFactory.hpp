/*
 * =====================================================================================
 *
 *       Filename:  PlayerFactory.hpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:36:44
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef PLAYERFACTORY_HPP_
#define PLAYERFACTORY_HPP_

#include "SceneObject.hpp"

class PlayerFactory {
	public:
		static SceneObject create(u16 x, u16 y, u16 clientId);

		static void playerCollisionAction(SceneObject &player, SceneObject &object, bool inCollision);

		static void checkOutOfMap(SceneObject &object);
};

#endif // PLAYERFACTORY_HPP_
