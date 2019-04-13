/*
 * =====================================================================================
 *
 *       Filename:  Button.cpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 00:14:51
 *
 *         Author:  Dylan Prinsaud, dylan.prinsaud@epitech.eu
 *
 * =====================================================================================
 */
#include <gk/audio/AudioPlayer.hpp>
#include <gk/core/Mouse.hpp>
#include <gk/resource/ResourceHandler.hpp>

#include "Button.hpp"

Button::Button(const std::string &text) {
	m_image.load("texture-gui-button");
	m_image.setScale(0.75f, 0.75f);

	m_text.setFont(gk::ResourceHandler::getInstance().get<gk::Font>("font-pdark"));
	m_text.setCharacterSize(25);
	m_text.setString(text);
	m_text.setPosition(m_image.width() / 2.0f - m_text.getLocalBounds().width / 2.0f,
	                   m_image.height() / 2.0f - m_text.getLocalBounds().height / 2.0f);
}

Button::Button(const std::string &text, int posX, int posY) : Button(text) {
	setPosition(posX, posY);
}

void Button::reset() {
	m_isPressed = false;
	m_hasReleased = false;
	m_hasMouse = false;

	m_image.setColor(gk::Color::White);
}

void Button::onEvent(const SDL_Event &event) {
	gk::IntRect rect{{(int)getPosition().x, (int)getPosition().y}, {m_image.width(), m_image.height()}};
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT)
			m_isPressed = gk::Mouse::isInRect(rect);
	}

	if (m_isPressed && event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			m_hasReleased = gk::Mouse::isInRect(rect);
			m_isPressed = false;

			if (m_hasReleased)
				gk::AudioPlayer::playSound("sound-button");
		}
	}

	if (event.type == SDL_MOUSEMOTION) {
		if (rect.contains(event.motion.x, event.motion.y)) {
			if (!m_hasMouse)
				gk::AudioPlayer::playSound("sound-hover");

			m_image.setColor(gk::Color(175, 175, 175));
			m_hasMouse = true;
		}
		else {
			m_image.setColor(gk::Color::White);
			m_hasMouse = false;
		}
	}
}

void Button::setPosition(int posX, int posY) {
	gk::Transformable::setPosition(posX, posY);
}

void Button::draw(gk::RenderTarget &target, gk::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(m_image, states);
	target.draw(m_text, states);
}

