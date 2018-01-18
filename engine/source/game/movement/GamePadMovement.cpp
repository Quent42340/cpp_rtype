/*
 * =====================================================================================
 *
 *       Filename:  GamePadMovement.cpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:42:00
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "GamePad.hpp"
#include "GamePadMovement.hpp"

#include "MovementComponent.hpp"

void GamePadMovement::process(SceneObject &object) {
	auto &movementComponent = object.get<MovementComponent>();

	if(GamePad::isKeyPressed(GameKey::Left)) {
		movementComponent.v.x = -1;
	}
	else if(GamePad::isKeyPressed(GameKey::Right)) {
		movementComponent.v.x = 1;
	}

	if(GamePad::isKeyPressed(GameKey::Up)) {
		movementComponent.v.y = -1;
	}
	else if(GamePad::isKeyPressed(GameKey::Down)) {
		movementComponent.v.y = 1;
	}

	// if((GamePad::isKeyPressed(GameKey::Left) || GamePad::isKeyPressed(GameKey::Right))
	// && (GamePad::isKeyPressed(GameKey::Up)   || GamePad::isKeyPressed(GameKey::Down))) {
	// 	movementComponent.v.x /= 1.4;
	// 	movementComponent.v.y /= 1.4;
	// }

	m_isFinished = true;
}

