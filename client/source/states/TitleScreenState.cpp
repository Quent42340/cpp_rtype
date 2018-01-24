/*
 * =====================================================================================
 *
 *       Filename:  TitleScreenState.cpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 22:06:41
 *
 *         Author:  Dylan Prinsaud, dylan.prinsaud@epitech.eu
 *
 * =====================================================================================
 */
#include <SFML/Audio/Music.hpp>

#include "ApplicationStateStack.hpp"
#include "AudioPlayer.hpp"
#include "Config.hpp"
#include "ResourceHandler.hpp"
#include "ServerConnectState.hpp"
// #include "PauseMenuState.hpp"
#include "TitleScreenState.hpp"

TitleScreenState::TitleScreenState() {
	m_rtype.setFont(ResourceHandler::getInstance().get<sf::Font>("font-pdark"));
	m_rtype.setString("RType");
	m_rtype.setCharacterSize(60);
	m_rtype.setFillColor(sf::Color::Green);
	m_rtype.setStyle(sf::Text::Bold);
	m_rtype.setPosition(Config::screenWidth / 2.0f - m_rtype.getLocalBounds().width / 2.0f + 5, 70);

	m_play.setPosition(Config::screenWidth / 2.0f - m_play.width() / 2.0, 240);
	m_exit.setPosition(Config::screenWidth / 2.0f - m_exit.width() / 2.0, 240 + m_exit.height() + 20);

	AudioPlayer::playMusic("music-theme");
}

void TitleScreenState::onEvent(sf::Event &event) {
	m_play.onEvent(event);
	m_exit.onEvent(event);
}

void TitleScreenState::update() {
	if (m_play.isPressed()) {
		m_play.reset();
		// m_stateStack->push<PauseMenuState>();
		m_stateStack->push<ServerConnectState>();
	}
	else if (m_exit.isPressed() == true)
		m_stateStack->pop();
}

void TitleScreenState::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(m_background, states);

	target.draw(m_rtype, states);

	target.draw(m_play, states);
	target.draw(m_exit, states);
}

