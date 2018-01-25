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

#include "Config.hpp"
#include "EasyMovement.hpp"
#include "HitboxComponent.hpp"
#include "LifetimeComponent.hpp"
#include "MovementComponent.hpp"
#include "Network.hpp"
#include "NetworkComponent.hpp"
#include "PositionComponent.hpp"
#include "SpriteComponent.hpp"
#include "TestBulletFactory.hpp"

SceneObject TestBulletFactory::create(const std::string &type, const std::string &textureName, const sf::Vector2f &pos, const sf::Vector2f &v, float speed) {
	static size_t bulletCount = 0;
	SceneObject object{"BasicBullet" + std::to_string(bulletCount++), type};
	object.set<PositionComponent>(pos);
	object.set<SpriteComponent>(textureName);
	object.set<NetworkComponent>();
	object.set<LifetimeComponent>(&TestBulletFactory::checkOutOfMap);
	object.set<MovementComponent>(new EasyMovement([v] (const SceneObject &object) {
		object.get<MovementComponent>().v = v;
	})).speed = speed;

	// FIXME: WARNING HARDCODED SIZE
	object.set<HitboxComponent>(0, 0, 16, 8);

	return object;
}

bool TestBulletFactory::checkOutOfMap(const SceneObject &object) {
	return (object.get<PositionComponent>().x + object.get<HitboxComponent>().currentHitbox()->width < 0 ||
	        object.get<PositionComponent>().x > Config::screenWidth ||
	        object.get<PositionComponent>().y + object.get<HitboxComponent>().currentHitbox()->height < 0 ||
	        object.get<PositionComponent>().y > Config::screenHeight);
}

