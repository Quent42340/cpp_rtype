/*
 * =====================================================================================
 *
 *       Filename:  MovementSystem.cpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:42:16
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "MovementSystem.hpp"

#include "CollisionComponent.hpp"
#include "MovementComponent.hpp"

void MovementSystem::process(SceneObject &object) {
	if(object.has<MovementComponent>()) {
		auto &movement = object.get<MovementComponent>();

		movement.movement->process(object);

		movement.isBlocked.x = false;
		movement.isBlocked.y = false;

		if((movement.v.x || movement.v.y)
		&& object.has<CollisionComponent>()) {
			object.get<CollisionComponent>().checkCollisions(object);
		}

		movement.isMoving = movement.v.x || movement.v.y;

		object.move(movement.v);
	}
}

