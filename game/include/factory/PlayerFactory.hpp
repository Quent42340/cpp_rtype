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

#include <gk/scene/SceneObject.hpp>

class PlayerFactory {
	public:
		static gk::SceneObject create(u16 x, u16 y, u16 clientId);

		static void playerCollisionAction(gk::SceneObject &player, gk::SceneObject &object, bool inCollision);

		static void checkOutOfMap(gk::SceneObject &object);
};

#endif // PLAYERFACTORY_HPP_
