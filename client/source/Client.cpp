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
#include <gk/audio/AudioPlayer.hpp>
#include <gk/core/input/GamePad.hpp>
#include <gk/core/input/InputHandler.hpp>
#include <gk/gui/Image.hpp>
#include <gk/gui/Sprite.hpp>
#include <gk/resource/ResourceHandler.hpp>
#include <gk/system/GameClock.hpp>

#include "Client.hpp"
#include "GameEndState.hpp"
#include "HitboxComponent.hpp"
#include "Network.hpp"
#include "NetworkComponent.hpp"
#include "PlayerComponent.hpp"
#include "PositionComponent.hpp"

void Client::connect(sf::IpAddress serverAddress, u16 serverPort) {
	m_serverAddress = serverAddress;
	m_serverPort = serverPort;

	m_tcpSocket.reset(new sf::TcpSocket);
	if (serverAddress.toInteger() == 0 || m_tcpSocket->connect(serverAddress, serverPort, sf::seconds(5)) != sf::Socket::Done)
		throw EXCEPTION("Network error: Unable to connect to server", serverAddress.toString() + ":" + std::to_string(serverPort));

	if (m_socket.bind(0) != sf::Socket::Done)
		throw EXCEPTION("Network error: Bind failed");

	sf::Packet packet;
	packet << Network::Command::ClientConnect << sf::IpAddress::getLocalAddress().toString() << m_socket.getLocalPort();
	m_tcpSocket->send(packet);

	sf::Packet answer;
	m_tcpSocket->receive(answer);

	Network::Command command;
	answer >> command;
	if (command == Network::Command::ClientRefused)
		throw EXCEPTION("Server error: You can't join an already started game.");

	if (command != Network::Command::ClientOk)
		throw EXCEPTION("Network error: Expected 'ClientOk' packet.");
	answer >> m_id;

	m_tcpSocket->setBlocking(false);
	m_socket.setBlocking(false);
}

void Client::disconnect() {
	sf::Packet packet;
	packet << Network::Command::ClientDisconnect;
	m_tcpSocket->send(packet);
}

void Client::sendReady() {
	sf::Packet packet;
	packet << Network::Command::ClientReady << m_id;
	m_tcpSocket->send(packet);
}

void Client::sendKeyState() {
	if (!m_keyUpdateTimer.isStarted())
		m_keyUpdateTimer.start();

	if (m_keyUpdateTimer.time() > 15) {
		gk::InputHandler *inputHandler = gk::GamePad::getInputHandler();
		if (inputHandler) {
			sf::Packet packet;
			packet << Network::Command::KeyState << gk::GameClock::getTicks() << m_id;
			for (auto &it : inputHandler->keysPressed()) {
				packet << static_cast<u8>(it.first) << it.second;
			}

			m_socket.send(packet, m_serverAddress, m_serverPort);
		}

		m_keyUpdateTimer.reset();
		m_keyUpdateTimer.start();
	}
}

void Client::update(gk::ApplicationStateStack &stateStack, Scene &scene, bool &hasGameStarted) {
	sf::Packet packet;
	sf::IpAddress senderAddress;
	u16 senderPort;
	while (m_socket.receive(packet, senderAddress, senderPort) == sf::Socket::Done) {
		Network::Command command;
		packet >> command;

		// std::cout << "UDP Message of type '" << Network::commandToString(command) << "' received from: " << senderAddress << ":" << senderPort << std::endl;

		if (command == Network::Command::EntityState)
			handleEntityStateMessage(scene, packet);
	}

	while (m_tcpSocket->receive(packet) == sf::Socket::Done) {
		Network::Command command;
		packet >> command;

		// std::cout << "TCP message of type '" << Network::commandToString(command) << "' received from: " << senderAddress << ":" << senderPort << std::endl;

		if (command == Network::Command::EntityDie && !handleEntityDieMessage(stateStack, scene, packet)) {
			break;
		}
		else if (command == Network::Command::EntitySpawn) {
			handleEntitySpawnMessage(scene, packet);
		}
		else if (command == Network::Command::GameStart) {
			hasGameStarted = true;
		}
		else if (command == Network::Command::GameWin) {
			disconnect();

			stateStack.push<GameEndState>(true);

			break;
		}
	}
}

void Client::handleEntityStateMessage(Scene &scene, sf::Packet &packet) {
	u32 timestamp;
	std::string entityName;
	gk::Vector2f pos;
	gk::Vector2f v;
	packet >> timestamp >> entityName >> pos.x >> pos.y >> v.x >> v.y;

	// std::cout << "New entity state at " << timestamp << ": " << entityName << " (" << pos.x << ";" << pos.y << ") moving at (" << v.x << ";" << v.y << ")" << std::endl;

	SceneObject *object = scene.objects().findByName(entityName);
	if (object) {

		auto &networkComponent = object->get<NetworkComponent>();
		if (networkComponent.lastUpdateTimestamp < timestamp) {
			networkComponent.lastUpdateTimestamp = timestamp;

			object->set<PositionComponent>(pos);

			if (object->has<PlayerComponent>()) {
				if (v.y == 0)
					object->get<gk::Sprite>().setCurrentAnimation(0);
				else if (v.y < 0)
					object->get<gk::Sprite>().setCurrentAnimation(2);
				else if (v.y > 0)
					object->get<gk::Sprite>().setCurrentAnimation(1);
			}
		}
	}
}

bool Client::handleEntityDieMessage(gk::ApplicationStateStack &stateStack, Scene &scene, sf::Packet &packet) {
	std::string entityName;
	packet >> entityName;

	// std::cout << "Entity die: " << entityName << std::endl;

	SceneObject *entity = scene.objects().findByName(entityName);
	if (entity) {
		if (entity->type() == "Enemy" && entity->get<PositionComponent>().x >= 0) {
			gk::AudioPlayer::playSound("sound-boom");

			static size_t boomEffectCount = 0;
			SceneObject boomEffect{"BoomEffect" + std::to_string(boomEffectCount++), "Effect"};
			boomEffect.set<PositionComponent>(entity->get<PositionComponent>());
			boomEffect.set<gk::Sprite>().load(gk::ResourceHandler::getInstance().get<gk::Sprite>("effect-boom-sprite"));
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
	gk::Vector2f pos;
	std::string textureName;
	packet >> entityName >> entityType >> pos.x >> pos.y;
	packet >> textureName;

	SceneObject object{entityName, entityType};
	object.set<PositionComponent>(pos);
	object.set<NetworkComponent>();
	if (gk::ResourceHandler::getInstance().has(textureName + "-sprite"))
		object.set<gk::Sprite>().load(gk::ResourceHandler::getInstance().get<gk::Sprite>(textureName + "-sprite"));
	else
		object.set<gk::Image>(textureName);

	if (entityType == "Player")
		object.set<PlayerComponent>(m_id);

	if (entityType == "PlayerBullet")
		gk::AudioPlayer::playSound("sound-bullet");

	scene.addObject(std::move(object));
}

