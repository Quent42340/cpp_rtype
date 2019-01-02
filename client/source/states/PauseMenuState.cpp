/*
 * =====================================================================================
 *
 *       Filename:  PauseMenuState.cpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 07:00:10
 *
 *         Author:  Dylan Prinsaud, dylan.prinsaud@epitech.eu
 *
 * =====================================================================================
 */
#include <gk/core/ApplicationStateStack.hpp>
#include <gk/resource/ResourceHandler.hpp>

#include "Config.hpp"
#include "GameEndState.hpp"
#include "PauseMenuState.hpp"
#include "TitleScreenState.hpp"

PauseMenuState::PauseMenuState() {
	m_text.setFont(gk::ResourceHandler::getInstance().get<gk::Font>("font-pdark"));
	m_text.setText("PAUSE");
	m_text.setCharacterSize(60);
	m_text.setColor(gk::Color::White);
	m_text.setStyle(gk::Text::Bold);

	m_text.setPosition(Config::screenWidth / 2.0f - m_text.getLocalBounds().width / 2.0f + 5, 40);

	m_resume.setPosition(Config::screenWidth / 2.0f - m_resume.width() / 2.0, 160);
	m_leave.setPosition(Config::screenWidth / 2.0f - m_leave.width() / 2.0, 160 + m_leave.height() + 20);
	m_exit.setPosition(Config::screenWidth / 2.0f - m_exit.width() / 2.0, 160 + m_leave.height() + m_exit.height() + 40);
}

void PauseMenuState::onEvent(const SDL_Event &event) {
	m_resume.onEvent(event);
	m_leave.onEvent(event);
	m_exit.onEvent(event);
}

void PauseMenuState::update() {
	if (m_resume.isPressed()) {
		m_stateStack->pop();
	}

	if (m_leave.isPressed()) {
		while (m_stateStack->size())
			m_stateStack->pop();
		m_stateStack->push<TitleScreenState>();
	}

	if (m_exit.isPressed())
		while (m_stateStack->size())
			m_stateStack->pop();
}

void PauseMenuState::draw(gk::RenderTarget &target, gk::RenderStates states) const {
	target.draw(m_background, states);

	target.draw(m_text, states);

	target.draw(m_resume, states);
	target.draw(m_leave, states);
	target.draw(m_exit, states);
}

