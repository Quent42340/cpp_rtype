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

#include "LifetimeComponent.hpp"
#include "MovementComponent.hpp"
#include "NetworkComponent.hpp"

void NetworkSystem::process(SceneObject &object) {
	if (object.has<NetworkComponent>()) {
		auto &networkComponent = object.get<NetworkComponent>();
		if (object.has<MovementComponent>()) {
			auto &movementComponent = object.get<MovementComponent>();
			if (movementComponent.isMoving && networkComponent.timer.time() > 20) {
				sf::Packet packet;
				packet << NetworkCommand::EntityMove << object.name() << object.getPosition().x << object.getPosition().y;
				Network::getInstance().socket().send(packet, sf::IpAddress::Broadcast, 4243);

				networkComponent.timer.reset();
				networkComponent.timer.start();
			}
		}

		if (object.has<LifetimeComponent>()) {
			auto &lifetimeComponent = object.get<LifetimeComponent>();
			if (lifetimeComponent.dead(object)) {
				sf::Packet packet;
				packet << NetworkCommand::EntityDie << object.name();
				Network::getInstance().socket().send(packet, sf::IpAddress::Broadcast, 4243);
			}
		}
	}
}

