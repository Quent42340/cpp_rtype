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

#include <gk/scene/movement/EasyMovement.hpp>
#include <gk/scene/component/HitboxComponent.hpp>
#include <gk/scene/component/LifetimeComponent.hpp>
#include <gk/scene/component/MovementComponent.hpp>
#include <gk/scene/component/PositionComponent.hpp>

#include "Config.hpp"
#include "Network.hpp"
#include "NetworkComponent.hpp"
#include "SpriteComponent.hpp"
#include "TestBulletFactory.hpp"

gk::SceneObject TestBulletFactory::create(const std::string &type, const std::string &textureName, const gk::Vector2f &pos, const gk::Vector2f &v, float speed) {
	static size_t bulletCount = 0;
	gk::SceneObject object{"BasicBullet" + std::to_string(bulletCount++), type};
	object.set<gk::PositionComponent>(pos);
	object.set<SpriteComponent>(textureName);
	object.set<NetworkComponent>();
	object.set<gk::LifetimeComponent>(&TestBulletFactory::checkOutOfMap);
	object.set<gk::MovementComponent>(new gk::EasyMovement([v] (const gk::SceneObject &object) {
		object.get<gk::MovementComponent>().v = v;
	})).speed = speed;

	// FIXME: WARNING HARDCODED SIZE
	object.set<gk::HitboxComponent>(0, 0, 16, 8);

	return object;
}

bool TestBulletFactory::checkOutOfMap(const gk::SceneObject &object) {
	return (object.get<gk::PositionComponent>().x + object.get<gk::HitboxComponent>().currentHitbox()->width < 0 ||
	        object.get<gk::PositionComponent>().x > Config::screenWidth ||
	        object.get<gk::PositionComponent>().y + object.get<gk::HitboxComponent>().currentHitbox()->height < 0 ||
	        object.get<gk::PositionComponent>().y > Config::screenHeight);
}

