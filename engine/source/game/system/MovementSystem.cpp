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
#include "PositionComponent.hpp"

void MovementSystem::process(SceneObject &object) {
	if(object.has<MovementComponent>()) {
		auto &movement = object.get<MovementComponent>();

		if(movement.movements.size() != 0 && movement.movements.top()) {
			movement.movements.top()->process(object);
		}

		movement.isBlocked = false;
	}

	if(object.has<CollisionComponent>()) {
		object.get<CollisionComponent>().checkCollisions(object);
	}

	if(object.has<MovementComponent>()) {
		auto &movement = object.get<MovementComponent>();

		movement.isMoving = (movement.v.x || movement.v.y) ? true : false;

		object.get<PositionComponent>() += movement.v * movement.speed;

		movement.v.x = 0;
		movement.v.y = 0;
	}
}

