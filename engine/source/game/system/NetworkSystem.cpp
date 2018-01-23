/*
 * =====================================================================================
 *
 *       Filename:  NetworkSystem.cpp
 *
 *    Description:
 *
 *        Created:  22/01/2018 16:46:35
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Network.hpp"
#include "NetworkSystem.hpp"
#include "ServerInfo.hpp"

#include "LifetimeComponent.hpp"
#include "MovementComponent.hpp"
#include "NetworkComponent.hpp"
#include "SpriteComponent.hpp"

void NetworkSystem::process(SceneObject &object) {
	if (object.has<NetworkComponent>()) {
		auto &networkComponent = object.get<NetworkComponent>();
		if (!networkComponent.hasSpawned) {
			sf::Packet packet;
			packet << NetworkCommand::EntitySpawn;
			packet << object.name() << object.type() << object.getPosition().x << object.getPosition().y;

			auto &spriteComponent = object.get<SpriteComponent>();
			packet << spriteComponent.textureName() << spriteComponent.frameWidth() << spriteComponent.frameHeight() << spriteComponent.initialFrame();

			for (Client &client : ServerInfo::getInstance().clients()) {
				client.tcpSocket->send(packet);
			}

			networkComponent.hasSpawned = true;
		}

		if (object.has<MovementComponent>()) {
			auto &movementComponent = object.get<MovementComponent>();
			if (movementComponent.isMoving && networkComponent.timer.time() > 20) {
				sf::Packet packet;
				packet << NetworkCommand::EntityMove << object.name() << object.getPosition().x << object.getPosition().y;
				for (const Client &client : ServerInfo::getInstance().clients()) {
					Network::getInstance().socket().send(packet, sf::IpAddress::Broadcast, client.port);
				}

				networkComponent.timer.reset();
				networkComponent.timer.start();
			}
		}

		if (object.has<LifetimeComponent>()) {
			auto &lifetimeComponent = object.get<LifetimeComponent>();
			if (lifetimeComponent.dead(object)) {
				sf::Packet packet;
				packet << NetworkCommand::EntityDie << object.name();
				for (Client &client : ServerInfo::getInstance().clients()) {
					client.tcpSocket->send(packet);
				}
			}
		}
	}
}

