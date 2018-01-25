/*
 * =====================================================================================
 *
 *       Filename:  Client.cpp
 *
 *    Description:
 *
 *        Created:  25/01/2018 12:26:43
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "AudioPlayer.hpp"
#include "Client.hpp"
#include "GameEndState.hpp"
#include "HitboxComponent.hpp"
#include "Image.hpp"
#include "Network.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"
#include "ResourceHandler.hpp"
#include "Sprite.hpp"

#include "TestBulletFactory.hpp"
#include "TestEntityFactory.hpp"

void Client::connect(sf::IpAddress serverAddress, u16 serverPort) {
	m_tcpSocket.reset(new sf::TcpSocket);
	if (serverAddress.toInteger() == 0 || m_tcpSocket->connect(serverAddress, serverPort, sf::seconds(5)) != sf::Socket::Done)
		throw EXCEPTION("Network error: Unable to connect to server", serverAddress.toString() + ":" + std::to_string(serverPort));

	if (m_socket.bind(0) != sf::Socket::Done)
		throw EXCEPTION("Network error: Bind failed");

	sf::Packet packet;
	packet << NetworkCommand::ClientConnect << m_socket.getLocalPort();
	m_tcpSocket->send(packet);

	sf::Packet answer;
	m_tcpSocket->receive(answer);

	NetworkCommand command;
	answer >> command;
	if (command != NetworkCommand::ClientConnect)
		throw EXCEPTION("Network error: Expected 'ClientConnect' packet.");
	answer >> m_id;

	m_tcpSocket->setBlocking(false);
	m_socket.setBlocking(false);
}

void Client::disconnect() {
	sf::Packet packet;
	packet << NetworkCommand::ClientDisconnect;
	m_tcpSocket->send(packet);
}

void Client::sendReady() {
	sf::Packet packet;
	packet << NetworkCommand::ClientReady << m_id;
	m_tcpSocket->send(packet);
}

void Client::sendKey(u32 key, bool isPressed) {
	sf::Packet packet;
	packet << (isPressed ? NetworkCommand::KeyPressed : NetworkCommand::KeyReleased);
	packet << m_id << key;
	m_socket.send(packet, sf::IpAddress::Broadcast, 4242);
}

void Client::update(ApplicationStateStack &stateStack, Scene &scene, bool &hasGameStarted) {
	sf::Packet packet;
	sf::IpAddress senderAddress;
	u16 senderPort;
	while (m_socket.receive(packet, senderAddress, senderPort) == sf::Socket::Done) {
		NetworkCommand command;
		packet >> command;
		// std::cout << "Message of type '" << Network::commandToString(command) << "' received from: " << senderAddress << ":" << senderPort << std::endl;

		if (command == NetworkCommand::EntityState)
			handleEntityStateMessage(scene, packet);
	}

	while (m_tcpSocket->receive(packet) == sf::Socket::Done) {
		NetworkCommand command;
		packet >> command;

		// std::cout << "Message of type '" << Network::commandToString(command) << "' received from: " << senderAddress << ":" << senderPort << std::endl;

		if (command == NetworkCommand::EntityDie && !handleEntityDieMessage(stateStack, scene, packet)) {
			break;
		}
		else if (command == NetworkCommand::EntitySpawn) {
			handleEntitySpawnMessage(scene, packet);
		}
		else if (command == NetworkCommand::GameStart) {
			hasGameStarted = true;
		}
		else if (command == NetworkCommand::GameWin) {
			disconnect();

			stateStack.push<GameEndState>(true);

			break;
		}
	}
}

void Client::handleEntityStateMessage(Scene &scene, sf::Packet &packet) {
	std::string entityName;
	sf::Vector2f pos;
	sf::Vector2f v;
	packet >> entityName >> pos.x >> pos.y >> v.x >> v.y;

	// std::cout << "Movement: " << entityName << " (" << pos.x << ";" << pos.y << ")" << std::endl;

	SceneObject *object = scene.objects().findByName(entityName);
	if (object) {
		object->set<PositionComponent>(pos);

		if (object->has<PlayerComponent>()) {
			if (v.y == 0)
				object->get<Sprite>().setCurrentAnimation(0);
			else if (v.y < 0)
				object->get<Sprite>().setCurrentAnimation(2);
			else if (v.y > 0)
				object->get<Sprite>().setCurrentAnimation(1);
		}
	}
}

bool Client::handleEntityDieMessage(ApplicationStateStack &stateStack, Scene &scene, sf::Packet &packet) {
	std::string entityName;
	packet >> entityName;

	// std::cout << "Entity die: " << entityName << std::endl;

	SceneObject *entity = scene.objects().findByName(entityName);
	if (entity) {
		if (entity->type() == "Enemy" && entity->get<PositionComponent>().x >= 0) {
			AudioPlayer::playSound("sound-boom");

			static size_t boomEffectCount = 0;
			SceneObject boomEffect{"BoomEffect" + std::to_string(boomEffectCount++), "Effect"};
			boomEffect.set<PositionComponent>(entity->get<PositionComponent>());
			boomEffect.set<Sprite>(ResourceHandler::getInstance().get<Sprite>("effect-boom-sprite"));
			scene.addObject(std::move(boomEffect));
		}

		if (entity->has<PlayerComponent>() && entity->get<PlayerComponent>().clientId() == m_id) {
			disconnect();

			stateStack.push<GameEndState>(false);

			return false;
		}

		scene.objects().removeByName(entityName);
	}

	return true;
}

void Client::handleEntitySpawnMessage(Scene &scene, sf::Packet &packet) {
	std::string entityName;
	std::string entityType;
	sf::Vector2f pos;
	std::string textureName;
	packet >> entityName >> entityType >> pos.x >> pos.y;
	packet >> textureName;

	SceneObject object{entityName, entityType};
	object.set<PositionComponent>(pos);
	if (ResourceHandler::getInstance().has(textureName + "-sprite"))
		object.set<Sprite>(ResourceHandler::getInstance().get<Sprite>(textureName + "-sprite"));
	else
		object.set<Image>(textureName);

	if (entityName == "Player" + std::to_string(m_id))
		object.set<PlayerComponent>(m_id);

	if (entityType == "PlayerBullet")
		AudioPlayer::playSound("sound-bullet");

	scene.addObject(std::move(object));
}

