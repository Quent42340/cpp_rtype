/*
 * =====================================================================================
 *
 *       Filename:  TextInput.cpp
 *
 *    Description:
 *
 *        Created:  22/01/2018 14:52:35
 *
 *         Author:  Dylan Prinsaud, dylan.prinsaud@epitech.eu
 *
 * =====================================================================================
 */
#include "AudioPlayer.hpp"
#include "ResourceHandler.hpp"
#include "TextInput.hpp"

TextInput::TextInput() {
	m_rectText.setFillColor(sf::Color::Black);
	m_rectText.setOutlineThickness(2);
	m_rectText.setOutlineColor(sf::Color::White);

	m_text.setFont(ResourceHandler::getInstance().get<sf::Font>("font-default"));
	m_text.setCharacterSize(25);
	m_text.setString("|");
}

void TextInput::setPosition(float x, float y) {
	m_rectText.setPosition(x, y);
	m_text.setPosition(x + 7, y + 7);
}

void TextInput::setSize(u16 width, u16 height) {
	m_rectText.setSize(sf::Vector2f(width, height));
}

void TextInput::onEvent(sf::Event &event) {
  	if (event.type == sf::Event::TextEntered) {
		if (event.text.unicode < 128) { // && m_inputTimer.time() - m_lastTimeKeyPressed[event.text.unicode] > 200) {
			if (event.text.unicode == '\b' && m_content.size() > 0) {
				m_content.erase(m_content.begin() + m_content.length() - 1);
				AudioPlayer::playSound("sound-keyboard");
			}
			else if (isprint(event.text.unicode) && (!m_characterLimit || m_content.size() < m_characterLimit)) {
				m_content += static_cast<char>(event.text.unicode);
				AudioPlayer::playSound("sound-keyboard");
			}

			m_text.setString(m_content + "|");
		}
	}
}

void TextInput::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(m_rectText, states);
	target.draw(m_text, states);
}

