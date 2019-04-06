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
#include <gk/core/Mouse.hpp>
#include <gk/resource/AudioPlayer.hpp>
#include <gk/resource/ResourceHandler.hpp>

#include "Button.hpp"

Button::Button(const std::string &text) {
	m_image.load("texture-gui-button");
	m_image.setScale(0.75f, 0.75f);

	m_text.setFont(gk::ResourceHandler::getInstance().get<sf::Font>("font-pdark"));
	m_text.setCharacterSize(25);
	m_text.setString(text);
	m_text.setPosition(m_image.width()  / 2.0f - m_text.getLocalBounds().width  / 2.0f,
	                   m_image.height() / 2.0f - m_text.getLocalBounds().height / 2.0f - 4);
}

Button::Button(const std::string &text, int posX, int posY) : Button(text) {
	setPosition(posX, posY);
}

void Button::reset() {
	m_isPressed = false;
	m_hasReleased = false;
	m_hasMouse = false;

	m_image.setColor(sf::Color::White);
}

void Button::onEvent(const sf::Event &event) {
	sf::IntRect rect{{(int)getPosition().x, (int)getPosition().y}, {m_image.width(), m_image.height()}};
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left)
			m_isPressed = rect.contains(event.mouseButton.x, event.mouseButton.y);
	}

	if (m_isPressed && event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			m_hasReleased = rect.contains(event.mouseButton.x, event.mouseButton.y);
			m_isPressed = false;

			if (m_hasReleased)
				gk::AudioPlayer::playSound("sound-button");
		}
	}

	if (event.type == sf::Event::MouseMoved) {
		if (rect.contains(event.mouseMove.x, event.mouseMove.y)) {
			if (!m_hasMouse)
				gk::AudioPlayer::playSound("sound-hover");

			m_image.setColor(sf::Color(175, 175, 175));
			m_hasMouse = true;
		}
		else {
			m_image.setColor(sf::Color::White);
			m_hasMouse = false;
		}
	}
}

void Button::setPosition(int posX, int posY) {
	sf::Transformable::setPosition(posX, posY);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(m_image, states);
	target.draw(m_text, states);
}

