/*
 * =====================================================================================
 *
 *       Filename:  BossFactory.cpp
 *
 *    Description:
 *
 *        Created:  25/01/2018 00:32:26
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/core/Timer.hpp>
#include <gk/scene/behaviour/EasyBehaviour.hpp>
#include <gk/scene/component/BehaviourComponent.hpp>
#include <gk/scene/component/HealthComponent.hpp>
#include <gk/scene/component/HitboxComponent.hpp>
#include <gk/scene/component/LifetimeComponent.hpp>
#include <gk/scene/component/MovementComponent.hpp>
#include <gk/scene/component/PositionComponent.hpp>
#include <gk/scene/movement/EasyMovement.hpp>
#include <gk/scene/SceneObjectList.hpp>

#include "BossFactory.hpp"
#include "Config.hpp"
#include "Network.hpp"
#include "NetworkComponent.hpp"
#include "SpriteComponent.hpp"
#include "TestBulletFactory.hpp"

gk::SceneObject BossFactory::create() {
	static size_t bossCount = 0;
	gk::SceneObject object{"Boss" + std::to_string(bossCount++), "Boss"};
	object.set<gk::PositionComponent>(Config::screenWidth, -10);
	object.set<NetworkComponent>();
	object.set<gk::SceneObjectList>();
	object.set<gk::Timer>().start();
	object.set<gk::HealthComponent>(10000);
	object.set<gk::LifetimeComponent>([&] (const gk::SceneObject &object) {
		return object.get<gk::HealthComponent>().life() == 0;
	});

	object.set<gk::MovementComponent>(new gk::EasyMovement([] (gk::SceneObject &object) {
		if (object.get<gk::PositionComponent>().x > Config::screenWidth - object.get<gk::HitboxComponent>().currentHitbox()->width) {
			object.get<gk::MovementComponent>().v.x = -1;
		}
	})).speed = 0.8f;

	object.set<SpriteComponent>("boss-boss1");
	object.set<gk::HitboxComponent>(0, 0, 268, 518);

	auto &collisionComponent = object.set<gk::CollisionComponent>();
	collisionComponent.addAction(&BossFactory::bossCollisionAction);

	auto &behaviourComponent = object.set<gk::BehaviourComponent>();
	behaviourComponent.addBehaviour<gk::EasyBehaviour>("Update", [] (gk::SceneObject &object) {
		gk::Timer &timer = object.get<gk::Timer>();
		if (timer.time() > 500 && !object.get<gk::LifetimeComponent>().dead(object)) {
			gk::Vector2f bulletPosition = object.get<gk::PositionComponent>() + gk::Vector2f{0, (float)object.get<gk::HitboxComponent>().currentHitbox()->height / 2};
			object.get<gk::SceneObjectList>().addObject(TestBulletFactory::create("EnemyBullet", "bullet-small", bulletPosition, {-1, -1}, 1.5f));
			object.get<gk::SceneObjectList>().addObject(TestBulletFactory::create("EnemyBullet", "bullet-small", bulletPosition, {-1,  0}, 1.5f));
			object.get<gk::SceneObjectList>().addObject(TestBulletFactory::create("EnemyBullet", "bullet-small", bulletPosition, {-1,  1}, 1.5f));

			timer.reset();
			timer.start();
		}
	});

	return object;
}

void BossFactory::bossCollisionAction(gk::SceneObject &enemy, gk::SceneObject &object, bool inCollision) {
	if (inCollision && object.type() == "PlayerBullet"
	 && !enemy.get<gk::LifetimeComponent>().dead(enemy)
	 && !object.get<gk::LifetimeComponent>().dead(object)) {
		// TODO: Create BulletComponent with damage
		enemy.get<gk::HealthComponent>().removeLife(100);
		object.get<gk::LifetimeComponent>().kill();
	}
}

// bool TestEnemyFactory::checkOutOfMap(const SceneObject &object) {
// 	return (object.get<PositionComponent>().x + object.get<HitboxComponent>().currentHitbox()->width < 0 ||
// 	        object.get<PositionComponent>().y + object.get<HitboxComponent>().currentHitbox()->height < 0);
// }


