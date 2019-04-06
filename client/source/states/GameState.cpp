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
#include <gk/core/input/GamePad.hpp>
#include <gk/core/ApplicationStateStack.hpp>
#include <gk/graphics/Sprite.hpp>
#include <gk/resource/AudioPlayer.hpp>
#include <gk/resource/ResourceHandler.hpp>
#include <gk/scene/controller/LifetimeController.hpp>
#include <gk/scene/view/SpriteView.hpp>

#include "Config.hpp"
#include "GameKey.hpp"
#include "GameState.hpp"
#include "Network.hpp"

GameState::GameState(const sf::IpAddress &serverAddress, u16 serverPort) {
	m_client.connect(serverAddress, serverPort);

	gk::AudioPlayer::playMusic("music-game");

	m_background2.setPosition(m_background.width() - 2.0f, 0);

	m_readyText.setFont(gk::ResourceHandler::getInstance().get<sf::Font>("font-pdark"));
	m_readyText.setString("Press Start when you're ready");
	m_readyText.setCharacterSize(30);
	m_readyText.setFillColor(sf::Color::White);
	m_readyText.setStyle(sf::Text::Bold);
	m_readyText.setPosition(Config::screenWidth  / 2.0f - m_readyText.getLocalBounds().width  / 2.0f,
	                        Config::screenHeight / 2.0f - m_readyText.getLocalBounds().height / 2.0f);

	m_scene.addController<gk::LifetimeController>();
	m_scene.addView<gk::SpriteView>();
}

void GameState::onEvent(const sf::Event &event) {
	if((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	 || event.type == sf::Event::Closed) {
		m_client.disconnect();

		while (m_stateStack->size())
			m_stateStack->pop();
	}
}

void GameState::update() {
	m_client.update(*m_stateStack, m_scene, m_hasGameStarted);

	if (m_hasGameStarted) {
		m_client.sendKeyState();

		if (m_background2.getPosition().x > Config::screenWidth - m_background2.width()) {
			m_background.move(-0.1f, 0.0f);
			m_background2.move(-0.1f, 0.0f);
		}

		// FIXME: Use LifetimeController
		for (size_t i = 0 ; i < m_scene.objects().size() ; ++i) {
			gk::SceneObject &object = m_scene.objects()[i];
			if (object.has<gk::Sprite>()) {
				auto &sprite = object.get<gk::Sprite>();
				sprite.updateAnimations();

				if (object.type() == "Effect" && sprite.hasAnimations() && sprite.currentAnimation().isFinished()) {
					m_scene.objects().remove(i--);
				}
			}
		}

		m_scene.update();
	}
	else if (gk::GamePad::isKeyPressedOnce(GameKey::Start)) {
		m_client.sendReady();

		m_readyText.setString("Waiting for other players...");
		m_readyText.setPosition(Config::screenWidth / 2.0f - m_readyText.getLocalBounds().width / 2.0f,
		                        Config::screenHeight / 2.0f - m_readyText.getLocalBounds().height / 2.0f);
	}
}

void GameState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(m_background2, states);
	target.draw(m_background, states);

	if (!m_hasGameStarted)
		target.draw(m_readyText, states);

	target.draw(m_scene, states);
}

