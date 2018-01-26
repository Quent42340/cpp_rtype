/*
 * =====================================================================================
 *
 *       Filename:  CollisionHelper.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:39:25
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef COLLISIONHELPER_HPP_
#define COLLISIONHELPER_HPP_

#include "SceneObject.hpp"

class CollisionHelper {
	public:
		static void checkCollision(SceneObject &object1, SceneObject &object2);

		static bool inCollision(SceneObject &object1, SceneObject &object2);
};

#endif // COLLISIONHELPER_HPP_
