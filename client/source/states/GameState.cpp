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
#include <SFML/Audio/Music.hpp>

#include "AudioPlayer.hpp"
#include "Config.hpp"
#include "DrawingSystem.hpp"
#include "GamePad.hpp"
#include "GameState.hpp"
#include "Network.hpp"
#include "NetworkCommandHandler.hpp"
#include "ResourceHandler.hpp"
#include "Sprite.hpp"

GameState::GameState(const sf::IpAddress &serverAddress, u16 serverPort) {
	Network::getInstance().connect(serverAddress, serverPort);

	AudioPlayer::playMusic("music-game");

	m_background2.setPosition(m_background.width() - 2.0f, 0);

	m_readyText.setFont(ResourceHandler::getInstance().get<sf::Font>("font-pdark"));
	m_readyText.setString("Press Start when you're ready");
	m_readyText.setCharacterSize(30);
	m_readyText.setFillColor(sf::Color::White);
	m_readyText.setStyle(sf::Text::Bold);
	m_readyText.setPosition(Config::screenWidth / 2.0f - m_readyText.getLocalBounds().width / 2.0f,
	                        Config::screenHeight / 2.0f - m_readyText.getLocalBounds().height / 2.0f);
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
	NetworkCommandHandler::update(*m_stateStack, m_scene, m_hasGameStarted);

	if (m_hasGameStarted) {
		if (m_background2.getPosition().x > Config::screenWidth - m_background2.width()) {
			m_background.move(-0.1f, 0.0f);
			m_background2.move(-0.1f, 0.0f);
		}
	}
	else if (GamePad::isKeyPressedOnce(GameKey::Start)) {
		NetworkCommandHandler::sendReady();

		m_readyText.setString("Waiting for other players...");
		m_readyText.setPosition(Config::screenWidth / 2.0f - m_readyText.getLocalBounds().width / 2.0f,
		                        Config::screenHeight / 2.0f - m_readyText.getLocalBounds().height / 2.0f);
	}

	// FIXME
	for(const SceneObject &object : m_scene.objects())
		if (object.has<Sprite>())
			object.get<Sprite>().updateAnimations();

	// m_scene.update();
}

void GameState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(m_background2, states);
	target.draw(m_background, states);

	if (!m_hasGameStarted)
		target.draw(m_readyText, states);

	// FIXME
	for(const SceneObject &object : m_scene.objects())
		DrawingSystem::draw(object, target, states);

	// target.draw(m_scene, states);
}

