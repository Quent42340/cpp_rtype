/*
 * =====================================================================================
 *
 *       Filename:  GenericEnemyFactory.cpp
 *
 *    Description:
 *
 *        Created:  25/01/2018 11:19:12
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <cmath>

#include <gk/core/Timer.hpp>

#include <gk/scene/behaviour/EasyBehaviour.hpp>
#include <gk/scene/component/BehaviourComponent.hpp>
#include <gk/scene/component/CollisionComponent.hpp>
#include <gk/scene/component/HealthComponent.hpp>
#include <gk/scene/component/HitboxComponent.hpp>
#include <gk/scene/component/LifetimeComponent.hpp>
#include <gk/scene/component/MovementComponent.hpp>
#include <gk/scene/component/PositionComponent.hpp>
#include <gk/scene/movement/EasyMovement.hpp>
#include <gk/scene/SceneObjectList.hpp>

#include "GenericEnemyFactory.hpp"
#include "Network.hpp"
#include "NetworkComponent.hpp"
#include "SpriteComponent.hpp"
#include "TestBulletFactory.hpp"

gk::SceneObject GenericEnemyFactory::create(const EnemyInfo &info, const gk::Vector2f &pos) {
	static size_t enemyCount = 0;
	gk::SceneObject object{info.name + std::to_string(enemyCount++), "Enemy"};
	object.set<gk::PositionComponent>(pos);
	object.set<NetworkComponent>();
	object.set<gk::SceneObjectList>();
	object.set<gk::Timer>().start();
	object.set<gk::HealthComponent>(info.health);
	object.set<gk::LifetimeComponent>([&] (const gk::SceneObject &object) {
		return checkOutOfMap(object) || object.get<gk::HealthComponent>().life() == 0;
	});

	object.set<gk::MovementComponent>(new gk::EasyMovement([&] (gk::SceneObject &object) {
		object.get<gk::MovementComponent>().v.x = -1;
		if (info.movementType == "sinusoidal")
			object.get<gk::MovementComponent>().v.y = 3.0f * sin(object.get<gk::PositionComponent>().x * 2 * M_PI / 180.0f);
	})).speed = info.movementSpeed;

	object.set<SpriteComponent>(info.texture);
	object.set<gk::HitboxComponent>(info.hitboxPosition.x, info.hitboxPosition.y, info.hitboxSize.x, info.hitboxSize.y);

	auto &collisionComponent = object.set<gk::CollisionComponent>();
	collisionComponent.addAction(&GenericEnemyFactory::enemyCollisionAction);

	auto &behaviourComponent = object.set<gk::BehaviourComponent>();
	behaviourComponent.addBehaviour<gk::EasyBehaviour>("Update", [&] (gk::SceneObject &object) {
		gk::Timer &timer = object.get<gk::Timer>();
		if (timer.time() > 1000 && !object.get<gk::LifetimeComponent>().dead(object)) {
			gk::Vector2f bulletPosition = object.get<gk::PositionComponent>() + gk::Vector2f{0, (float)object.get<gk::HitboxComponent>().currentHitbox()->height / 2 - 4};
			for (const BulletInfo &bulletInfo : info.bulletsInfo) {
				object.get<gk::SceneObjectList>().addObject(TestBulletFactory::create("EnemyBullet", "bullet-small", bulletPosition, {bulletInfo.velocity.x, bulletInfo.velocity.y}, bulletInfo.speed));
			}

			// object.get<SceneObjectList>().addObject(TestBulletFactory::create("EnemyBullet", "bullet-small", bulletPosition, {-1,  1}, 2.0f));
			// object.get<SceneObjectList>().addObject(TestBulletFactory::create("EnemyBullet", "bullet-small", bulletPosition, { 1, -1}, 2.0f));
			// object.get<SceneObjectList>().addObject(TestBulletFactory::create("EnemyBullet", "bullet-small", bulletPosition, { 1,  1}, 2.0f));

			timer.reset();
			timer.start();
		}
	});

	return object;
}

void GenericEnemyFactory::enemyCollisionAction(gk::SceneObject &enemy, gk::SceneObject &object, bool inCollision) {
	if (inCollision && object.type() == "PlayerBullet"
	 && !enemy.get<gk::LifetimeComponent>().dead(enemy)
	 && !object.get<gk::LifetimeComponent>().dead(object)) {
		// TODO: Create BulletComponent with damage
		enemy.get<gk::HealthComponent>().removeLife(100);
		object.get<gk::LifetimeComponent>().kill();
	}
}

bool GenericEnemyFactory::checkOutOfMap(const gk::SceneObject &object) {
	return (object.get<gk::PositionComponent>().x + object.get<gk::HitboxComponent>().currentHitbox()->width < 0 ||
	        object.get<gk::PositionComponent>().y + object.get<gk::HitboxComponent>().currentHitbox()->height < 0);
}

