/*
 * =====================================================================================
 *
 *       Filename:  GameState.cpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:45:11
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Application.hpp"
#include "GameState.hpp"
#include "ResourceHandler.hpp"
#include "Scene.hpp"

#include "TestBulletFactory.hpp"
#include "TestEnemyFactory.hpp"
#include "TestEntityFactory.hpp"

GameState::GameState() {
	m_socket.bind(4243);
	m_socket.setBlocking(false);

	sf::Packet packet;
	packet << "ClientConnect";
	m_socket.send(packet, sf::IpAddress::Broadcast, 4242);

	// m_spawnTimer.start();
}

void GameState::update() {
	// if (m_spawnTimer.time() > 2000) {
	// 	m_spawnTimer.reset();
	// 	m_spawnTimer.start();
    //
	// 	m_scene.addObject(TestEnemyFactory::create({Application::screenWidth + 20, static_cast<float>(std::rand() % (Application::screenHeight - 40))}));
	// }

	sf::Packet packet;
	sf::IpAddress senderAddress;
	u16 senderPort;
	while (m_socket.receive(packet, senderAddress, senderPort) == sf::Socket::Done) {
		std::string packetType;
		packet >> packetType;
		std::cout << "Message of type '" << packetType << "' received from: " << senderAddress << ":" << senderPort << std::endl;

		if (packetType == "EntityMove") {
			std::string entityName;
			sf::Uint64 timestamp;
			sf::Vector2f pos;
			packet >> timestamp >> entityName >> pos.x >> pos.y;

			SceneObject *object = m_scene.objects().findByName(entityName);
			if (object)
				object->setPosition(pos);
		}
		else if (packetType == "EntitySpawn") {
			std::string entityName;
			std::string entityType;
			u16 port;
			sf::Vector2f pos;
			packet >> entityName >> entityType >> port >> pos.x >> pos.y;

			m_scene.addObject(TestEntityFactory::createClient(entityName, entityType, port, pos.x, pos.y));
		}
		else if (packetType == "BulletSpawn") {
			std::string entityName;
			std::string entityType;
			u16 port;
			std::string textureName;
			sf::Vector2f pos;
			packet >> entityName >> entityType >> port >> textureName >> pos.x >> pos.y;

			m_scene.addObject(TestBulletFactory::createClient(entityName, textureName, pos));
		}
	}

	m_background.move(-0.03, 0);

	// m_scene.update();
}

void GameState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	// target.setView(view);

	target.draw(m_background, states);
	target.draw(m_scene, states);

	// target.setView(target.getDefaultView());
}

