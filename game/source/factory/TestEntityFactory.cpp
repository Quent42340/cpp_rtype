/*
 * =====================================================================================
 *
 *       Filename:  TestEntityFactory.cpp
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
#include "EasyBehaviour.hpp"
#include "GamePad.hpp"
#include "GamePadMovement.hpp"
#include "HitboxComponent.hpp"
#include "MovementComponent.hpp"
#include "Network.hpp"
#include "NetworkComponent.hpp"
#include "PlayerComponent.hpp"
#include "SceneObjectList.hpp"
#include "SpriteComponent.hpp"
#include "TestBulletFactory.hpp"
#include "TestEntityFactory.hpp"

SceneObject TestEntityFactory::create(u16 x, u16 y, u16 clientId) {
	static size_t playerCount = 0;
	SceneObject object{"Player" + std::to_string(playerCount++), "Player"};
	object.set<SceneObjectList>();
	object.set<PlayerComponent>(clientId);
	object.set<MovementComponent>(new GamePadMovement);
	object.set<NetworkComponent>();
	object.setPosition(x, y);

	auto &spriteComponent = object.set<SpriteComponent>("characters-players", 34, 18);
	object.set<HitboxComponent>(0, 0, spriteComponent.frameWidth(), spriteComponent.frameHeight());

	auto &behaviourComponent = object.set<BehaviourComponent>();
	behaviourComponent.addBehaviour<EasyBehaviour>("Update", [] (SceneObject &object) {
		if (GamePad::isKeyPressedWithDelay(GameKey::Start, 200)) {
			auto &hitboxComponent = object.get<HitboxComponent>();
			sf::Vector2f bulletPosition = object.getPosition() + sf::Vector2f{(float)hitboxComponent.currentHitbox()->width, (float)hitboxComponent.currentHitbox()->height / 2 - 4};
			object.get<SceneObjectList>().addObject(TestBulletFactory::create("PlayerBullet", "bullets-basic", bulletPosition, {1, 0}));
		}
	});

	return object;
}

