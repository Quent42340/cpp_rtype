/*
 * =====================================================================================
 *
 *       Filename:  MovementController.cpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:18:19
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "MovementController.hpp"

#include "CollisionComponent.hpp"
#include "MovementComponent.hpp"
#include "PositionComponent.hpp"

void MovementController::update(SceneObject &object) {
	if(object.has<MovementComponent>()) {
		auto &movement = object.get<MovementComponent>();

		movement.v.x = 0;
		movement.v.y = 0;

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
	}
}

