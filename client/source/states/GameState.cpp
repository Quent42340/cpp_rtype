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
#include "DrawingSystem.hpp"
#include "GameState.hpp"
#include "NetworkCommandHandler.hpp"

#include "Network.hpp"

GameState::GameState(const sf::IpAddress &serverAddress, u16 serverPort) {
	Network::getInstance().connect(serverAddress, serverPort);
}

void GameState::onEvent(sf::Event &event) {
	if (event.type == sf::Event::KeyPressed) {
		NetworkCommandHandler::sendKey(event.key.code, true);
	}
	else if (event.type == sf::Event::KeyReleased) {
		NetworkCommandHandler::sendKey(event.key.code, false);
	}
}

void GameState::update() {
	NetworkCommandHandler::update(m_scene);

	m_background.move(-0.1f, 0.0f);

	// m_scene.update();
}

void GameState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(m_background, states);

	for(const SceneObject &object : m_scene.objects())
		DrawingSystem::draw(object, target, states);
	// target.draw(m_scene, states);
}

