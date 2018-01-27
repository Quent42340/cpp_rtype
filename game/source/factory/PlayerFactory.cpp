/*
 * =====================================================================================
 *
 *       Filename:  PlayerFactory.cpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:37:18
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "BehaviourComponent.hpp"
#include "CollisionComponent.hpp"
#include "Config.hpp"
#include "EasyBehaviour.hpp"
#include "GamePad.hpp"
#include "GamePadMovement.hpp"
#include "HealthComponent.hpp"
#include "HitboxComponent.hpp"
#include "LifetimeComponent.hpp"
#include "MovementComponent.hpp"
#include "Network.hpp"
#include "NetworkComponent.hpp"
#include "PlayerComponent.hpp"
#include "PlayerFactory.hpp"
#include "PositionComponent.hpp"
#include "SceneObjectList.hpp"
#include "SpriteComponent.hpp"
#include "TestBulletFactory.hpp"

SceneObject PlayerFactory::create(u16 x, u16 y, u16 clientId) {
	static size_t playerCount = 0;
	SceneObject object{"Player" + std::to_string(playerCount++), "Player"};
	object.set<SceneObjectList>();
	object.set<PlayerComponent>(clientId);
	object.set<MovementComponent>(new GamePadMovement).speed = 1.5f;
	object.set<NetworkComponent>();
	object.set<HealthComponent>(500);
	object.set<LifetimeComponent>([&] (const SceneObject &object) {
		return object.get<HealthComponent>().life() == 0;
	});
	object.set<PositionComponent>(x, y);

	auto &collisionComponent = object.set<CollisionComponent>();
	collisionComponent.addAction(&playerCollisionAction);
	collisionComponent.addChecker(&checkOutOfMap);

	object.set<SpriteComponent>("spaceship-player" + std::to_string(clientId + 1));
	object.set<HitboxComponent>(0, 0, 33, 15);

	auto &behaviourComponent = object.set<BehaviourComponent>();
	behaviourComponent.addBehaviour<EasyBehaviour>("Update", [] (SceneObject &object) {
		if (GamePad::isKeyPressedWithDelay(GameKey::A, 200) && !object.get<LifetimeComponent>().dead(object)) {
			auto &hitboxComponent = object.get<HitboxComponent>();
			sf::Vector2f bulletPosition = object.get<PositionComponent>() + sf::Vector2f{(float)hitboxComponent.currentHitbox()->width, (float)hitboxComponent.currentHitbox()->height / 2 - 4};
			object.get<SceneObjectList>().addObject(TestBulletFactory::create("PlayerBullet", "bullet-basic", bulletPosition, {1, 0}, 4.0f));
		}
	});

	return object;
}

void PlayerFactory::playerCollisionAction(SceneObject &player, SceneObject &object, bool inCollision) {
	if (inCollision && (object.type() == "EnemyBullet" || object.type() == "Enemy" || object.type() == "Boss")
	 && !player.get<LifetimeComponent>().dead(player)
	 && !object.get<LifetimeComponent>().dead(object)) {
		// TODO: Create BulletComponent with damage
		player.get<HealthComponent>().removeLife(100);

		if (object.type() == "EnemyBullet")
			object.get<LifetimeComponent>().kill();
	}
}

void PlayerFactory::checkOutOfMap(SceneObject &object) {
	auto &movementComponent = object.get<MovementComponent>();
	if (object.get<PositionComponent>().x + movementComponent.v.x + object.get<HitboxComponent>().currentHitbox()->width > Config::screenWidth
	 || object.get<PositionComponent>().x + movementComponent.v.x < 0)
		movementComponent.v.x = 0;
	if (object.get<PositionComponent>().y + movementComponent.v.y + object.get<HitboxComponent>().currentHitbox()->height > Config::screenHeight
	 || object.get<PositionComponent>().y + movementComponent.v.y < 0)
		movementComponent.v.y = 0;
}

