/*
 * =====================================================================================
 *
 *       Filename:  NetworkCommandHandler.cpp
 *
 *    Description:
 *
 *        Created:  22/01/2018 14:40:42
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "AudioPlayer.hpp"
#include "Direction.hpp"
#include "GameEndState.hpp"
#include "Image.hpp"
#include "Network.hpp"
#include "NetworkCommandHandler.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "Sprite.hpp"

#include "TestBulletFactory.hpp"
#include "TestEnemyFactory.hpp"
#include "TestEntityFactory.hpp"

void NetworkCommandHandler::disconnect() {
	sf::Packet packet;
	packet << NetworkCommand::ClientDisconnect;
	Network::getInstance().tcpSocket().send(packet);
}

void NetworkCommandHandler::sendReady() {
	sf::Packet packet;
	packet << NetworkCommand::ClientReady << Network::getInstance().clientId();
	Network::getInstance().tcpSocket().send(packet);
}

void NetworkCommandHandler::sendKey(u32 key, bool isPressed) {
	sf::Packet packet;
	packet << (isPressed ? NetworkCommand::KeyPressed : NetworkCommand::KeyReleased);
	packet << Network::getInstance().clientId() << key;
	Network::getInstance().socket().send(packet, sf::IpAddress::Broadcast, 4242);
}

void NetworkCommandHandler::update(ApplicationStateStack &stateStack, Scene &scene, bool &hasGameStarted) {
	sf::Packet packet;
	sf::IpAddress senderAddress;
	u16 senderPort;
	while (Network::getInstance().socket().receive(packet, senderAddress, senderPort) == sf::Socket::Done) {
		NetworkCommand command;
		packet >> command;
		// std::cout << "Message of type '" << Network::commandToString(command) << "' received from: " << senderAddress << ":" << senderPort << std::endl;

		if (command == NetworkCommand::EntityMove) {
			std::string entityName;
			sf::Vector2f pos;
			bool isMoving;
			u8 direction;
			packet >> entityName >> pos.x >> pos.y >> isMoving >> direction;

			// std::cout << "Movement: " << entityName << " (" << pos.x << ";" << pos.y << ")" << std::endl;

			SceneObject *object = scene.objects().findByName(entityName);
			if (object) {
				object->set<PositionComponent>(pos);

				if (object->has<PlayerComponent>()) {
					if (isMoving) {
						if (static_cast<Direction>(direction) == Direction::Up)
							object->get<Sprite>().setCurrentFrame(4);
						else if (static_cast<Direction>(direction) == Direction::Down)
							object->get<Sprite>().setCurrentFrame(0);
					}
					else {
						object->get<Sprite>().setCurrentFrame(2);
					}
				}
			}
		}
	}

	while (Network::getInstance().tcpSocket().receive(packet) == sf::Socket::Done) {
		NetworkCommand command;
		packet >> command;

		// std::cout << "Message of type '" << Network::commandToString(command) << "' received from: " << senderAddress << ":" << senderPort << std::endl;

		if (command == NetworkCommand::EntityDie) {
			std::string entityName;
			packet >> entityName;

			std::cout << "Entity die: " << entityName << std::endl;

			SceneObject *entity = scene.objects().findByName(entityName);
			if (entity) {
				if (entity->type() == "Enemy" && entity->get<PositionComponent>().x >= 0)
					AudioPlayer::playSound("sound-boom");

				if (entity->has<PlayerComponent>() && entity->get<PlayerComponent>().clientId() == Network::getInstance().clientId()) {
					disconnect();

					stateStack.push<GameEndState>(false);
				}

				scene.objects().removeByName(entityName);
			}
		}
		else if (command == NetworkCommand::EntitySpawn) {
			std::string entityName;
			std::string entityType;
			sf::Vector2f pos;
			std::string textureName;
			sf::Vector2<u16> frameSize;
			u16 initialFrame;
			packet >> entityName >> entityType >> pos.x >> pos.y;
			packet >> textureName >> frameSize.x >> frameSize.y >> initialFrame;

			SceneObject object{entityName, entityType};
			object.set<PositionComponent>(pos);
			if (frameSize.x == 0 && frameSize.y == 0)
				object.set<Image>(textureName);
			else
				object.set<Sprite>(textureName, frameSize.x, frameSize.y).setCurrentFrame(initialFrame);

			if (entityName == "Player" + std::to_string(Network::getInstance().clientId()))
				object.set<PlayerComponent>(Network::getInstance().clientId());

			if (entityType == "PlayerBullet")
				AudioPlayer::playSound("sound-bullet");

			scene.addObject(std::move(object));
		}
		else if (command == NetworkCommand::GameStart) {
			hasGameStarted = true;
		}
		else if (command == NetworkCommand::GameWin) {
			disconnect();

			stateStack.push<GameEndState>(true);
		}
	}
}

