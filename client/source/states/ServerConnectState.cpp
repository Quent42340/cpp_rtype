/*
 * =====================================================================================
 *
 *       Filename:  ServerConnectState.cpp
 *
 *    Description:
 *
 *        Created:  24/01/2018 02:58:44
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/core/ApplicationStateStack.hpp>
#include <gk/core/input/GamePad.hpp>
#include <gk/resource/ResourceHandler.hpp>

#include "Config.hpp"
#include "GameKey.hpp"
#include "GameState.hpp"
#include "ServerConnectState.hpp"

ServerConnectState::ServerConnectState() {
	m_text.setFont(gk::ResourceHandler::getInstance().get<sf::Font>("font-pdark"));
	m_text.setCharacterSize(60);
	m_text.setFillColor(sf::Color::White);
	m_text.setStyle(sf::Text::Bold);
	m_text.setString("Server address");
	m_text.setPosition(Config::screenWidth / 2.0f - m_text.getLocalBounds().width / 2.0f + 5, 70);

	m_errorText.setFont(gk::ResourceHandler::getInstance().get<sf::Font>("font-pdark"));
	m_errorText.setCharacterSize(20);
	m_errorText.setStyle(sf::Text::Bold);

	m_serverAddressInput.setCharacterLimit(15);
	m_serverAddressInput.setSize(400, 50);
	m_serverAddressInput.setPosition(Config::screenWidth / 2.0f - m_serverAddressInput.getSize().x / 2.0f, 200);

	m_back.setPosition(Config::screenWidth / 2.0f - m_back.width() / 2.0, 350);
}

void ServerConnectState::onEvent(const sf::Event &event) {
	m_serverAddressInput.onEvent(event);
	m_back.onEvent(event);
}

void ServerConnectState::update() {
	if (m_errorTimer.time() > 3000) {
		m_errorTimer.reset();
		m_errorText.setString("");
	}

	if (m_isConnecting) {
		m_isConnecting = false;

		try {
			m_stateStack->push<GameState>(m_serverAddressInput.content());
		}
		catch (gk::Exception &e) {
			std::cerr << "Error " << e.what() << std::endl;

			m_errorText.setFillColor(sf::Color::Red);
			m_errorText.setString("Can't connect to server!");
			m_errorText.setPosition(Config::screenWidth / 2.0f - m_errorText.getLocalBounds().width / 2.0f + 5, 280);

			m_errorTimer.reset();
			m_errorTimer.start();
		}
	}

	if (gk::GamePad::isKeyPressedOnce(GameKey::Start)) {
		m_errorText.setFillColor(sf::Color::White);
		m_errorText.setString("Connecting...");
		m_errorText.setPosition(Config::screenWidth / 2.0f - m_errorText.getLocalBounds().width / 2.0f + 5, 280);

		m_isConnecting = true;
	}

	if (m_back.isPressed()) {
		m_stateStack->pop();
	}
}

void ServerConnectState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(m_background, states);

	target.draw(m_text, states);
	target.draw(m_errorText, states);

	target.draw(m_serverAddressInput, states);

	target.draw(m_back, states);
}

