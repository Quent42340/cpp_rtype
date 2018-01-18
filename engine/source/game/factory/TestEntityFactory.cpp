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
#include "Image.hpp"
#include "MovementComponent.hpp"
#include "TestEntityFactory.hpp"

SceneObject TestEntityFactory::create(u16 x, u16 y) {
	SceneObject object{"TestEntity", "Test"};
	object.set<Image>("test-entity");
	object.set<MovementComponent>(new GamePadMovement);
	object.setPosition(x, y);

	return object;
}

