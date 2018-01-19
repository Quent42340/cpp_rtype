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
#include "MovementComponent.hpp"
#include "SceneObjectList.hpp"
#include "Sprite.hpp"
#include "TestBulletFactory.hpp"
#include "TestEntityFactory.hpp"

SceneObject TestEntityFactory::create(u16 x, u16 y) {
	SceneObject object{"Player1", "Player"};
	object.set<SceneObjectList>();
	object.set<Sprite>("characters-players", 34, 18).setCurrentFrame(0);
	object.set<MovementComponent>(new GamePadMovement);
	object.setPosition(x, y);

	auto &behaviourComponent = object.set<BehaviourComponent>();
	behaviourComponent.addBehaviour<EasyBehaviour>("Update", [] (SceneObject &object) {
		if (GamePad::isKeyPressedWithDelay(GameKey::Start, 250)) {
			// FIXME: WARNING HARDCODED SIZE
			sf::Vector2f bulletPosition = object.getPosition() + sf::Vector2f{34, 18 / 2 - 4};
			object.get<SceneObjectList>().addObject(TestBulletFactory::create(bulletPosition, {1, 0}));
		}
	});

	return object;
}

