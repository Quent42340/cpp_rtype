/*
 * =====================================================================================
 *
 *       Filename:  NetworkController.cpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:23:47
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Network.hpp"
#include "NetworkController.hpp"
#include "ServerInfo.hpp"

#include "LifetimeComponent.hpp"
#include "MovementComponent.hpp"
#include "NetworkComponent.hpp"
#include "SpriteComponent.hpp"
#include "PositionComponent.hpp"

void NetworkController::update(SceneObject &object) {
	if (object.has<NetworkComponent>()) {
		auto &networkComponent = object.get<NetworkComponent>();
		auto &positionComponent = object.get<PositionComponent>();

		bool hasGameStarted = true;
		for (Client &client : ServerInfo::getInstance().clients()) {
			if (!client.isReady)
				hasGameStarted = false;
		}

		if (!networkComponent.hasSpawned && hasGameStarted) {
			sf::Packet packet;
			packet << Network::Command::EntitySpawn;
			packet << object.name() << object.type() << positionComponent.x << positionComponent.y;

			auto &spriteComponent = object.get<SpriteComponent>();
			packet << spriteComponent.textureName();

			for (Client &client : ServerInfo::getInstance().clients()) {
				client.tcpSocket->send(packet);
			}

			networkComponent.hasSpawned = true;
		}

		if (object.has<MovementComponent>()) {
			auto &movementComponent = object.get<MovementComponent>();
			if (networkComponent.timer.time() > 20) {
				sf::Packet packet;
				packet << Network::Command::EntityState << object.name();
				packet << positionComponent.x << positionComponent.y;
				packet << movementComponent.v.x << movementComponent.v.y;
				for (const Client &client : ServerInfo::getInstance().clients()) {
					m_socket.send(packet, sf::IpAddress::Broadcast, client.port);
				}

				networkComponent.timer.reset();
				networkComponent.timer.start();
			}
		}

		if (object.has<LifetimeComponent>()) {
			auto &lifetimeComponent = object.get<LifetimeComponent>();
			if (lifetimeComponent.dead(object) && !lifetimeComponent.areClientsNotified()) {
				sf::Packet packet;
				packet << (object.type() != "Boss" ? Network::Command::EntityDie : Network::Command::GameWin) << object.name();

				for (Client &client : ServerInfo::getInstance().clients()) {
					client.tcpSocket->send(packet);
				}

				lifetimeComponent.setClientsNotified(true);
			}
		}
	}
}

