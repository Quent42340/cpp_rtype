/*
 * =====================================================================================
 *
 *       Filename:  TestEnemyFactory.cpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 05:38:18
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Application.hpp"
#include "BehaviourComponent.hpp"
#include "EasyBehaviour.hpp"
#include "EasyMovement.hpp"
#include "HealthComponent.hpp"
#include "HitboxComponent.hpp"
#include "LifetimeComponent.hpp"
#include "MovementComponent.hpp"
#include "Network.hpp"
#include "NetworkComponent.hpp"
#include "SceneObjectList.hpp"
#include "Sprite.hpp"
#include "TestBulletFactory.hpp"
#include "TestEnemyFactory.hpp"

SceneObject TestEnemyFactory::createClient(const std::string &name, const sf::Vector2f &pos) {
	SceneObject object{name, "Enemy"};
	object.set<Sprite>("characters-enemy1", 33, 33).setCurrentFrame(0);
	object.setPosition(pos);

	return object;
}

SceneObject TestEnemyFactory::createServer(const sf::Vector2f &pos) {
	static size_t enemyCount = 0;
	SceneObject object{"TestEnemy" + std::to_string(enemyCount++), "Enemy"};
	object.setPosition(pos);
	object.set<NetworkComponent>();
	object.set<SceneObjectList>();
	object.set<Timer>().start();
	object.set<HealthComponent>(500);
	object.set<LifetimeComponent>([&] (const SceneObject &object) {
		return checkOutOfMap(object) || object.get<HealthComponent>().life() == 0;
	});

	object.set<MovementComponent>(new EasyMovement([] (SceneObject &object) {
		object.get<MovementComponent>().v.x = -1;
	})).speed = 0.8f;

	// FIXME: WARNING HARDCODED SIZE
	object.set<HitboxComponent>(0, 0, 33, 33);

	auto &collisionComponent = object.set<CollisionComponent>();
	collisionComponent.addAction(&TestEnemyFactory::enemyCollisionAction);

	auto &behaviourComponent = object.set<BehaviourComponent>();
	behaviourComponent.addBehaviour<EasyBehaviour>("Update", [] (SceneObject &object) {
		Timer &timer = object.get<Timer>();
		if (timer.time() > 1000) {
			sf::Vector2f bulletPosition = object.getPosition() + sf::Vector2f{0, (float)object.get<HitboxComponent>().currentHitbox()->height / 2 - 4};
			object.get<SceneObjectList>().addObject(TestBulletFactory::createServer("bullets-small", bulletPosition, {-1, 0}));

			timer.reset();
			timer.start();
		}
	});

	sf::Packet packet;
	packet << NetworkCommand::EntitySpawn << object.name() << object.type() << object.getPosition().x << object.getPosition().y;
	Network::getInstance().socket().send(packet, sf::IpAddress::Broadcast, 4243);

	return object;
}

void TestEnemyFactory::enemyCollisionAction(SceneObject &enemy, SceneObject &object, bool inCollision) {
	// FIXME: WARNING NAME CHECK
	if (inCollision && object.name() == "BasicBullet"
	 && !enemy.get<LifetimeComponent>().dead(enemy)
	 && !object.get<LifetimeComponent>().dead(object)) {
		// TODO: Create BulletComponent with damage
		enemy.get<HealthComponent>().removeLife(100);
		object.get<LifetimeComponent>().kill();
	}
}

bool TestEnemyFactory::checkOutOfMap(const SceneObject &object) {
	return (object.getPosition().x + object.get<HitboxComponent>().currentHitbox()->width < 0 ||
	        object.getPosition().y + object.get<HitboxComponent>().currentHitbox()->height < 0);
}

