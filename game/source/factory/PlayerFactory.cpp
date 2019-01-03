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
#include <gk/core/input/GamePad.hpp>

#include <gk/scene/behaviour/EasyBehaviour.hpp>
#include <gk/scene/component/BehaviourComponent.hpp>
#include <gk/scene/component/CollisionComponent.hpp>
#include <gk/scene/component/HealthComponent.hpp>
#include <gk/scene/component/HitboxComponent.hpp>
#include <gk/scene/component/LifetimeComponent.hpp>
#include <gk/scene/component/MovementComponent.hpp>
#include <gk/scene/component/PositionComponent.hpp>
#include <gk/scene/movement/GamePadMovement.hpp>
#include <gk/scene/SceneObjectList.hpp>

#include "Config.hpp"
#include "GameKey.hpp"
#include "Network.hpp"
#include "NetworkComponent.hpp"
#include "PlayerComponent.hpp"
#include "PlayerFactory.hpp"
#include "SpriteComponent.hpp"
#include "TestBulletFactory.hpp"

gk::SceneObject PlayerFactory::create(u16 x, u16 y, u16 clientId) {
	static size_t playerCount = 0;
	gk::SceneObject object{"Player" + std::to_string(playerCount++), "Player"};
	object.set<gk::SceneObjectList>();
	object.set<PlayerComponent>(clientId);
	object.set<NetworkComponent>();
	object.set<gk::HealthComponent>(500);
	object.set<gk::LifetimeComponent>([&] (const gk::SceneObject &object) {
		return object.get<gk::HealthComponent>().life() == 0;
	});
	object.set<gk::PositionComponent>(x, y);

	auto *movement = new gk::GamePadMovement;
	movement->setKeys(GameKey::Left, GameKey::Right, GameKey::Up, GameKey::Down);
	object.set<gk::MovementComponent>(movement).speed = 1.5f;

	auto &collisionComponent = object.set<gk::CollisionComponent>();
	collisionComponent.addAction(&playerCollisionAction);
	collisionComponent.addChecker(&checkOutOfMap);

	object.set<SpriteComponent>("spaceship-player" + std::to_string(clientId + 1));
	object.set<gk::HitboxComponent>(0, 0, 33, 15);

	auto &behaviourComponent = object.set<gk::BehaviourComponent>();
	behaviourComponent.addBehaviour<gk::EasyBehaviour>("Update", [] (gk::SceneObject &object) {
		if (gk::GamePad::isKeyPressedWithDelay(GameKey::A, 200) && !object.get<gk::LifetimeComponent>().dead(object)) {
			auto &hitboxComponent = object.get<gk::HitboxComponent>();
			gk::Vector2f bulletPosition = object.get<gk::PositionComponent>() + gk::Vector2f{(float)hitboxComponent.currentHitbox()->width, (float)hitboxComponent.currentHitbox()->height / 2 - 4};
			object.get<gk::SceneObjectList>().addObject(TestBulletFactory::create("PlayerBullet", "bullet-basic", bulletPosition, {1, 0}, 4.0f));
		}
	});

	return object;
}

void PlayerFactory::playerCollisionAction(gk::SceneObject &player, gk::SceneObject &object, bool inCollision) {
	if (inCollision && (object.type() == "EnemyBullet" || object.type() == "Enemy" || object.type() == "Boss")
	 && !player.get<gk::LifetimeComponent>().dead(player)
	 && !object.get<gk::LifetimeComponent>().dead(object)) {
		// TODO: Create BulletComponent with damage
		player.get<gk::HealthComponent>().removeLife(100);

		if (object.type() == "EnemyBullet")
			object.get<gk::LifetimeComponent>().kill();
	}
}

void PlayerFactory::checkOutOfMap(gk::SceneObject &object) {
	auto &movementComponent = object.get<gk::MovementComponent>();
	if (object.get<gk::PositionComponent>().x + movementComponent.v.x + object.get<gk::HitboxComponent>().currentHitbox()->width > Config::screenWidth
	 || object.get<gk::PositionComponent>().x + movementComponent.v.x < 0)
		movementComponent.v.x = 0;
	if (object.get<gk::PositionComponent>().y + movementComponent.v.y + object.get<gk::HitboxComponent>().currentHitbox()->height > Config::screenHeight
	 || object.get<gk::PositionComponent>().y + movementComponent.v.y < 0)
		movementComponent.v.y = 0;
}

