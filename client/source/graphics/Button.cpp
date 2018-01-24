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
#include "AudioPlayer.hpp"
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

void Button::reset() {
	m_isPressed = false;
	m_hasReleased = false;
	m_hasMouse = false;

	m_image.setTileColor(0, sf::Color::White);
}

void Button::onEvent(sf::Event &event) {
	sf::FloatRect rect{getPosition(), {(float)m_image.width(), (float)m_image.height()}};
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.mouseButton.button == sf::Mouse::Left)
			m_isPressed = Mouse::isInRect(rect);
	}

	if (m_isPressed && event.type == sf::Event::MouseButtonReleased) {
		if (event.mouseButton.button == sf::Mouse::Left) {
			m_hasReleased = Mouse::isInRect(rect);
			m_isPressed = false;

			if (m_hasReleased)
				AudioPlayer::playSound("sound-button");
		}
	}

	if (event.type == sf::Event::MouseMoved) {
		if (rect.contains(event.mouseMove.x, event.mouseMove.y)) {
			if (!m_hasMouse)
				AudioPlayer::playSound("sound-hover");

			m_image.setTileColor(0, sf::Color(175, 175, 175));
			m_hasMouse = true;
		}
		else {
			m_image.setTileColor(0, sf::Color::White);
			m_hasMouse = false;
		}
	}
}

void Button::setPosition(int posX, int posY) {
	sf::Transformable::setPosition(posX, posY);
	m_text.setPosition(m_image.width() / 2.0f - m_text.getLocalBounds().width / 2.0f,
	                   m_image.height() / 2.0f - m_text.getLocalBounds().height / 2.0f - 4);
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	states.transform *= getTransform();

	target.draw(m_image, states);
	target.draw(m_text, states);
}

