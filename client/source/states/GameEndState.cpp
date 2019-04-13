/*
 * =====================================================================================
 *
 *       Filename:  GameEndState.cpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 08:29:18
 *
 *         Author:  Dylan Prinsaud, dylan.prinsaud@epitech.eu
 *
 * =====================================================================================
 */
#include <iostream>

#include <gk/audio/AudioPlayer.hpp>
#include <gk/core/ApplicationStateStack.hpp>
#include <gk/resource/ResourceHandler.hpp>

#include "Config.hpp"
#include "GameEndState.hpp"
#include "TitleScreenState.hpp"

GameEndState::GameEndState(bool isWinner) {
	m_text.setFont(gk::ResourceHandler::getInstance().get<gk::Font>("font-pdark"));
	m_text.setCharacterSize(60);
	m_text.setColor(gk::Color::White);
	m_text.setStyle(gk::Text::Bold);
	m_text.setString(isWinner ? "LEVEL CLEARED" : "GAME OVER");
	m_text.setPosition(Config::screenWidth / 2.0f - m_text.getLocalBounds().width / 2.0f + 5, 70);

	m_leave.setPosition(Config::screenWidth / 2.0f - m_leave.width() / 2.0, 240);
	m_exit.setPosition(Config::screenWidth / 2.0f - m_exit.width() / 2.0, 240 + m_exit.height() + 20);

	gk::AudioPlayer::playMusic(isWinner ? "music-victory" : "music-gameover");
}

void GameEndState::onEvent(const SDL_Event &event) {
	m_leave.onEvent(event);
	m_exit.onEvent(event);
}

void GameEndState::update() {
	if (m_leave.isPressed()) {
		while (m_stateStack->size())
			m_stateStack->pop();
		m_stateStack->push<TitleScreenState>();
	}

	if (m_exit.isPressed()) {
		while (m_stateStack->size())
			m_stateStack->pop();
	}

}

void GameEndState::draw(gk::RenderTarget &target, gk::RenderStates states) const {
	target.draw(m_background, states);

	target.draw(m_text, states);

	target.draw(m_leave, states);
	target.draw(m_exit, states);
}
