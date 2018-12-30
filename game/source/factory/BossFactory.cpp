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

#include "BehaviourComponent.hpp"
#include "BossFactory.hpp"
#include "Config.hpp"
#include "EasyBehaviour.hpp"
#include "EasyMovement.hpp"
#include "HealthComponent.hpp"
#include "HitboxComponent.hpp"
#include "LifetimeComponent.hpp"
#include "MovementComponent.hpp"
#include "Network.hpp"
#include "NetworkComponent.hpp"
#include "PositionComponent.hpp"
#include "SceneObjectList.hpp"
#include "SpriteComponent.hpp"
#include "TestBulletFactory.hpp"

SceneObject BossFactory::create() {
	static size_t bossCount = 0;
	SceneObject object{"Boss" + std::to_string(bossCount++), "Boss"};
	object.set<PositionComponent>(Config::screenWidth, -10);
	object.set<NetworkComponent>();
	object.set<SceneObjectList>();
	object.set<gk::Timer>().start();
	object.set<HealthComponent>(10000);
	object.set<LifetimeComponent>([&] (const SceneObject &object) {
		return object.get<HealthComponent>().life() == 0;
	});

	object.set<MovementComponent>(new EasyMovement([] (SceneObject &object) {
		if (object.get<PositionComponent>().x > Config::screenWidth - object.get<HitboxComponent>().currentHitbox()->width) {
			object.get<MovementComponent>().v.x = -1;
		}
	})).speed = 0.8f;

	object.set<SpriteComponent>("boss-boss1");
	object.set<HitboxComponent>(0, 0, 268, 518);

	auto &collisionComponent = object.set<CollisionComponent>();
	collisionComponent.addAction(&BossFactory::bossCollisionAction);

	auto &behaviourComponent = object.set<BehaviourComponent>();
	behaviourComponent.addBehaviour<EasyBehaviour>("Update", [] (SceneObject &object) {
		gk::Timer &timer = object.get<gk::Timer>();
		if (timer.time() > 500 && !object.get<LifetimeComponent>().dead(object)) {
			gk::Vector2f bulletPosition = object.get<PositionComponent>() + gk::Vector2f{0, (float)object.get<HitboxComponent>().currentHitbox()->height / 2};
			object.get<SceneObjectList>().addObject(TestBulletFactory::create("EnemyBullet", "bullet-small", bulletPosition, {-1, -1}, 1.5f));
			object.get<SceneObjectList>().addObject(TestBulletFactory::create("EnemyBullet", "bullet-small", bulletPosition, {-1,  0}, 1.5f));
			object.get<SceneObjectList>().addObject(TestBulletFactory::create("EnemyBullet", "bullet-small", bulletPosition, {-1,  1}, 1.5f));

			timer.reset();
			timer.start();
		}
	});

	return object;
}

void BossFactory::bossCollisionAction(SceneObject &enemy, SceneObject &object, bool inCollision) {
	// FIXME: WARNING NAME CHECK
	if (inCollision && object.type() == "PlayerBullet"
	 && !enemy.get<LifetimeComponent>().dead(enemy)
	 && !object.get<LifetimeComponent>().dead(object)) {
		// TODO: Create BulletComponent with damage
		enemy.get<HealthComponent>().removeLife(100);
		object.get<LifetimeComponent>().kill();
	}
}

// bool TestEnemyFactory::checkOutOfMap(const SceneObject &object) {
// 	return (object.get<PositionComponent>().x + object.get<HitboxComponent>().currentHitbox()->width < 0 ||
// 	        object.get<PositionComponent>().y + object.get<HitboxComponent>().currentHitbox()->height < 0);
// }


