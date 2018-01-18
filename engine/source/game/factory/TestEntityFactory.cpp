/*
 * =====================================================================================
 *
 *       Filename:  TestEntityFactory.cpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:37:18
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "GamePadMovement.hpp"
#include "Sprite.hpp"
#include "MovementComponent.hpp"
#include "TestEntityFactory.hpp"

SceneObject TestEntityFactory::create(u16 x, u16 y) {
	SceneObject object{"TestEntity", "Test"};
	object.set<Sprite>("characters-players", 34, 18).setCurrentFrame(0);
	object.set<MovementComponent>(new GamePadMovement);
	object.setPosition(x, y);

	return object;
}

