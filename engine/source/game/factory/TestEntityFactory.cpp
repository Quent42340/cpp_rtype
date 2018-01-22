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
#include <SFML/Network.hpp>

#include "BehaviourComponent.hpp"
#include "EasyBehaviour.hpp"
#include "GamePad.hpp"
#include "GamePadMovement.hpp"
#include "HitboxComponent.hpp"
#include "MovementComponent.hpp"
#include "NetworkComponent.hpp"
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
	object.set<sf::UdpSocket>().bind(0);

	auto &behaviourComponent = object.set<BehaviourComponent>();
	behaviourComponent.addBehaviour<EasyBehaviour>("Update", [] (SceneObject &object) {
		if (GamePad::isKeyPressedWithDelay(GameKey::Start, 200)) {
			Sprite &sprite = object.get<Sprite>();
			sf::Vector2f bulletPosition = object.getPosition() + sf::Vector2f{(float)sprite.frameWidth(), (float)sprite.frameHeight() / 2 - 4};
			object.get<SceneObjectList>().addObject(TestBulletFactory::create("bullets-basic", bulletPosition, {1, 0}));
		}
	});

	return object;
}

SceneObject TestEntityFactory::createClient(const std::string &name, const std::string &type, u16 port, u16 x, u16 y) {
	SceneObject object{name, type};
	object.set<SceneObjectList>();
	object.set<Sprite>("characters-players", 34, 18).setCurrentFrame(0);
	// object.set<MovementComponent>(new GamePadMovement);
	object.setPosition(x, y);

	return object;
}

SceneObject TestEntityFactory::createServer(u16 x, u16 y) {
	static size_t playerCount = 0;
	SceneObject object{"Player" + std::to_string(playerCount++), "Player"};
	object.set<SceneObjectList>();
	object.set<MovementComponent>(new GamePadMovement);
	object.setPosition(x, y);

	// FIXME: WARNING HARDCODED SIZE
	object.set<HitboxComponent>(0, 0, 34, 18);

	sf::UdpSocket &socket = object.set<NetworkComponent>().socket;
	socket.bind(0);

	sf::Packet packet;
	packet << "EntitySpawn" << object.name() << object.type() << socket.getLocalPort() << object.getPosition().x << object.getPosition().y;
	socket.send(packet, sf::IpAddress::Broadcast, 4243);

	auto &behaviourComponent = object.set<BehaviourComponent>();
	behaviourComponent.addBehaviour<EasyBehaviour>("Update", [] (SceneObject &object) {
		if (GamePad::isKeyPressedWithDelay(GameKey::Start, 200)) {
			auto &hitboxComponent = object.get<HitboxComponent>();
			sf::Vector2f bulletPosition = object.getPosition() + sf::Vector2f{(float)hitboxComponent.currentHitbox()->width, (float)hitboxComponent.currentHitbox()->height / 2 - 4};
			// object.get<SceneObjectList>().addObject(TestBulletFactory::create("bullets-basic", bulletPosition, {1, 0}));
			object.get<SceneObjectList>().addObject(TestBulletFactory::createServer("bullets-basic", bulletPosition, {1, 0}));
		}
	});

	return object;
}

