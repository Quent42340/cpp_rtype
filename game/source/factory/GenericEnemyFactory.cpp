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
#include "BehaviourComponent.hpp"
#include "CollisionComponent.hpp"
#include "EasyBehaviour.hpp"
#include "EasyMovement.hpp"
#include "GenericEnemyFactory.hpp"
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

SceneObject GenericEnemyFactory::create(const EnemyInfo &info, const sf::Vector2f &pos) {
	static size_t enemyCount = 0;
	SceneObject object{info.name + std::to_string(enemyCount++), "Enemy"};
	object.set<PositionComponent>(pos);
	object.set<NetworkComponent>();
	object.set<SceneObjectList>();
	object.set<Timer>().start();
	object.set<HealthComponent>(info.health);
	object.set<LifetimeComponent>([&] (const SceneObject &object) {
		return checkOutOfMap(object) || object.get<HealthComponent>().life() == 0;
	});

	object.set<MovementComponent>(new EasyMovement([] (SceneObject &object) {
		object.get<MovementComponent>().v.x = -1;
	})).speed = info.movementSpeed;

	object.set<SpriteComponent>(info.texture);
	object.set<HitboxComponent>(info.hitboxPosition.x, info.hitboxPosition.y, info.hitboxSize.x, info.hitboxSize.y);

	auto &collisionComponent = object.set<CollisionComponent>();
	collisionComponent.addAction(&GenericEnemyFactory::enemyCollisionAction);

	auto &behaviourComponent = object.set<BehaviourComponent>();
	behaviourComponent.addBehaviour<EasyBehaviour>("Update", [&] (SceneObject &object) {
		Timer &timer = object.get<Timer>();
		if (timer.time() > 1000 && !object.get<LifetimeComponent>().dead(object)) {
			sf::Vector2f bulletPosition = object.get<PositionComponent>() + sf::Vector2f{0, (float)object.get<HitboxComponent>().currentHitbox()->height / 2 - 4};
			for (const BulletInfo &bulletInfo : info.bulletsInfo) {
				object.get<SceneObjectList>().addObject(TestBulletFactory::create("EnemyBullet", "bullet-small", bulletPosition, {bulletInfo.velocity.x, bulletInfo.velocity.y}, bulletInfo.speed));
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

void GenericEnemyFactory::enemyCollisionAction(SceneObject &enemy, SceneObject &object, bool inCollision) {
	// FIXME: WARNING NAME CHECK
	if (inCollision && object.type() == "PlayerBullet"
	 && !enemy.get<LifetimeComponent>().dead(enemy)
	 && !object.get<LifetimeComponent>().dead(object)) {
		// TODO: Create BulletComponent with damage
		enemy.get<HealthComponent>().removeLife(100);
		object.get<LifetimeComponent>().kill();
	}
}

bool GenericEnemyFactory::checkOutOfMap(const SceneObject &object) {
	return (object.get<PositionComponent>().x + object.get<HitboxComponent>().currentHitbox()->width < 0 ||
	        object.get<PositionComponent>().y + object.get<HitboxComponent>().currentHitbox()->height < 0);
}

