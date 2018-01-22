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
#include "Network.hpp"
#include "NetworkCommandHandler.hpp"

#include "TestBulletFactory.hpp"
#include "TestEnemyFactory.hpp"
#include "TestEntityFactory.hpp"

void NetworkCommandHandler::connect() {
	sf::Packet packet;
	packet << NetworkCommand::ClientConnect;
	Network::getInstance().socket().send(packet, sf::IpAddress::Broadcast, 4242);
}

void NetworkCommandHandler::disconnect() {
	sf::Packet packet;
	packet << NetworkCommand::ClientDisconnect;
	Network::getInstance().socket().send(packet, sf::IpAddress::Broadcast, 4242);
}

void NetworkCommandHandler::sendKey(u32 key, bool isPressed) {
	sf::Packet packet;
	packet << (isPressed ? NetworkCommand::KeyPressed : NetworkCommand::KeyReleased) << key;
	Network::getInstance().socket().send(packet, sf::IpAddress::Broadcast, 4242);
}

void NetworkCommandHandler::update(Scene &scene) {
	sf::Packet packet;
	sf::IpAddress senderAddress;
	u16 senderPort;
	while (Network::getInstance().socket().receive(packet, senderAddress, senderPort) == sf::Socket::Done) {
		NetworkCommand command;
		packet >> command;
		std::cout << "Message of type '" << Network::commandToString(command) << "' received from: " << senderAddress << ":" << senderPort << std::endl;

		if (command == NetworkCommand::EntityMove) {
			std::string entityName;
			sf::Uint64 timestamp;
			sf::Vector2f pos;
			packet >> timestamp >> entityName >> pos.x >> pos.y;

			SceneObject *object = scene.objects().findByName(entityName);
			if (object)
				object->setPosition(pos);
		}
		else if (command == NetworkCommand::EntitySpawn) {
			std::string entityName;
			std::string entityType;
			u16 port;
			sf::Vector2f pos;
			packet >> entityName >> entityType >> port >> pos.x >> pos.y;

			scene.addObject(TestEntityFactory::createClient(entityName, entityType, port, pos.x, pos.y));
		}
		else if (command == NetworkCommand::BulletSpawn) {
			std::string entityName;
			std::string entityType;
			u16 port;
			std::string textureName;
			sf::Vector2f pos;
			packet >> entityName >> entityType >> port >> textureName >> pos.x >> pos.y;

			scene.addObject(TestBulletFactory::createClient(entityName, textureName, pos));
		}
	}
}

