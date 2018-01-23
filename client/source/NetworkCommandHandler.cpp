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
#include "Image.hpp"
#include "Network.hpp"
#include "NetworkCommandHandler.hpp"
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

void NetworkCommandHandler::sendKey(u32 key, bool isPressed) {
	sf::Packet packet;
	packet << (isPressed ? NetworkCommand::KeyPressed : NetworkCommand::KeyReleased);
	packet << Network::getInstance().clientId() << key;
	Network::getInstance().socket().send(packet, sf::IpAddress::Broadcast, 4242);
}

void NetworkCommandHandler::update(Scene &scene) {
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
			packet >> entityName >> pos.x >> pos.y;

			// std::cout << "Movement: " << entityName << " (" << pos.x << ";" << pos.y << ")" << std::endl;

			SceneObject *object = scene.objects().findByName(entityName);
			if (object)
				object->set<PositionComponent>(pos);
		}
	}

	while (Network::getInstance().tcpSocket().receive(packet) == sf::Socket::Done) {
		NetworkCommand command;
		packet >> command;

		if (command == NetworkCommand::EntityDie) {
			std::string entityName;
			packet >> entityName;

			scene.objects().removeByName(entityName);
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
				object.set<Sprite>(textureName, frameSize.x, frameSize.y).setCurrentFrame(0);

			scene.addObject(std::move(object));
		}
	}
}

