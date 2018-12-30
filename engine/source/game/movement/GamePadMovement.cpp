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
#include <gk/core/input/GamePad.hpp>

#include "GameKey.hpp"
#include "GamePadMovement.hpp"

#include "MovementComponent.hpp"

void GamePadMovement::process(SceneObject &object) {
	auto &movementComponent = object.get<MovementComponent>();

	if(gk::GamePad::isKeyPressed(GameKey::Left)) {
		movementComponent.v.x = -1;
	}
	else if(gk::GamePad::isKeyPressed(GameKey::Right)) {
		movementComponent.v.x = 1;
	}

	if(gk::GamePad::isKeyPressed(GameKey::Up)) {
		movementComponent.v.y = -1;
	}
	else if(gk::GamePad::isKeyPressed(GameKey::Down)) {
		movementComponent.v.y = 1;
	}

	m_isFinished = true;
}

