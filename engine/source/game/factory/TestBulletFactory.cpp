/*
 * =====================================================================================
 *
 *       Filename:  TestBulletFactory.cpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 03:25:09
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "EasyMovement.hpp"
#include "Image.hpp"
#include "MovementComponent.hpp"
#include "TestBulletFactory.hpp"

// TODO: Add a lifetime component and kill object if it went out of map
SceneObject TestBulletFactory::create(const sf::Vector2f &pos, const sf::Vector2f &v) {
	SceneObject object{"BasicBullet", "Bullet"};
	object.set<Image>("bullets-basic");
	object.set<MovementComponent>(new EasyMovement([v] (SceneObject &object) {
		object.get<MovementComponent>().v = v;
	})).speed = 2.0f;

	object.setPosition(pos);

	return object;
}

