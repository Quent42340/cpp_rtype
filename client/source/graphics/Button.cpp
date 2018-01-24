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
#include <SFML/Audio/Music.hpp>

#include "Button.hpp"
#include "Mouse.hpp"
#include "ResourceHandler.hpp"

Button::Button(const std::string &name) {
	m_image.load("gui-button");

	m_text.setFont(ResourceHandler::getInstance().get<sf::Font>("font-pdark"));
	m_text.setCharacterSize(25);
	m_text.setString(name);

	m_image.setScale(0.75f, 0.75f);
}

Button::Button(const std::string &name, int posX, int posY) : Button(name) {
	setPosition(posX, posY);
}

void Button::onEvent(sf::Event &event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::FloatRect rect{m_image.getPosition(), {(float)m_image.width(), (float)m_image.height()}};
		if (event.mouseButton.button == sf::Mouse::Left)
			m_isPressed = Mouse::isInRect(rect);
	}

	if (m_isPressed && event.type == sf::Event::MouseButtonReleased) {
		sf::FloatRect rect{m_image.getPosition(), {(float)m_image.width(), (float)m_image.height()}};
		if (event.mouseButton.button == sf::Mouse::Left) {
			m_hasReleased = Mouse::isInRect(rect);
			m_isPressed = false;

			ResourceHandler::getInstance().get<sf::Music>("sound-button").play();
		}
	}
}

void Button::setPosition(int posX, int posY) {
	m_image.setPosition(posX, posY);
	m_text.setPosition(posX + m_image.width() / 2.0f - m_text.getLocalBounds().width / 2.0f,
	                   posY + m_image.height() / 2.0f - m_text.getLocalBounds().height / 2.0f - 4);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(m_image, states);
	target.draw(m_text, states);
}

