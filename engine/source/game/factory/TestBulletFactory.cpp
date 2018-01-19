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
#include <cmath>

#include "Application.hpp"
#include "EasyMovement.hpp"
#include "HitboxComponent.hpp"
#include "Image.hpp"
#include "LifetimeComponent.hpp"
#include "MovementComponent.hpp"
#include "TestBulletFactory.hpp"

SceneObject TestBulletFactory::create(const std::string &textureName, const sf::Vector2f &pos, const sf::Vector2f &v) {
	SceneObject object{"BasicBullet", "Bullet"};
	object.set<LifetimeComponent>(&TestBulletFactory::checkOutOfMap);
	object.set<MovementComponent>(new EasyMovement([v] (SceneObject &object) {
		object.get<MovementComponent>().v = v;
	})).speed = 3.0f;

	auto &image = object.set<Image>(textureName);
	object.set<HitboxComponent>(0, 0, image.width(), image.height());

	object.setPosition(pos);

	return object;
}

bool TestBulletFactory::checkOutOfMap(SceneObject &object) {
	return (object.getPosition().x + object.get<HitboxComponent>().currentHitbox()->width < 0 ||
	        object.getPosition().x > Application::screenWidth ||
	        object.getPosition().y + object.get<HitboxComponent>().currentHitbox()->height < 0 ||
	        object.getPosition().y > Application::screenHeight);
}

