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
#include <gk/core/GameClock.hpp>

#include <gk/scene/component/LifetimeComponent.hpp>
#include <gk/scene/component/MovementComponent.hpp>
#include <gk/scene/component/PositionComponent.hpp>

#include "Network.hpp"
#include "NetworkController.hpp"
#include "NetworkComponent.hpp"
#include "SpriteComponent.hpp"

void NetworkController::update(gk::SceneObject &object) {
	if (object.has<NetworkComponent>()) {
		auto &networkComponent = object.get<NetworkComponent>();
		auto &positionComponent = object.get<gk::PositionComponent>();

		bool hasGameStarted = true;
		for (Client &client : m_serverInfo.clients()) {
			if (!client.isReady)
				hasGameStarted = false;
		}

		if (!networkComponent.hasSpawned && hasGameStarted) {
			sf::Packet packet;
			packet << Network::Command::EntitySpawn;
			packet << object.name() << object.type() << positionComponent.x << positionComponent.y;

			auto &spriteComponent = object.get<SpriteComponent>();
			packet << spriteComponent.textureName();

			for (Client &client : m_serverInfo.clients()) {
				client.tcpSocket->send(packet);
			}

			networkComponent.hasSpawned = true;
		}

		if (object.has<gk::MovementComponent>()) {
			auto &movementComponent = object.get<gk::MovementComponent>();
			if (networkComponent.timer.time() > 20) {
				sf::Packet packet;
				packet << Network::Command::EntityState;
				packet << gk::GameClock::getTicks() << object.name();
				packet << positionComponent.x << positionComponent.y;
				packet << movementComponent.v.x << movementComponent.v.y;
				for (const Client &client : m_serverInfo.clients()) {
					// std::cout << "Sending entity state for " << object.name() << " to " << client.address.toString() << ":" << client.port << std::endl;
					m_socket.send(packet, client.address, client.port);
				}

				networkComponent.timer.reset();
				networkComponent.timer.start();
			}
		}

		if (object.has<gk::LifetimeComponent>()) {
			auto &lifetimeComponent = object.get<gk::LifetimeComponent>();
			if (lifetimeComponent.dead(object) && !lifetimeComponent.areClientsNotified()) {
				sf::Packet packet;
				packet << (object.type() != "Boss" ? Network::Command::EntityDie : Network::Command::GameWin) << object.name();

				for (Client &client : m_serverInfo.clients()) {
					client.tcpSocket->send(packet);
				}

				lifetimeComponent.setClientsNotified(true);
			}
		}
	}
}

