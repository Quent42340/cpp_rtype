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
#include <gk/audio/AudioPlayer.hpp>
#include <gk/resource/ResourceHandler.hpp>

#include "TextInput.hpp"

TextInput::TextInput() {
	m_rectText.setColor(gk::Color::Black);
	m_rectText.setOutlineThickness(2);
	m_rectText.setOutlineColor(gk::Color::White);

	m_text.setFont(gk::ResourceHandler::getInstance().get<gk::Font>("font-default"));
	m_text.setCharacterSize(25);
	m_text.setText("|");
}

void TextInput::setPosition(float x, float y) {
	m_rectText.setPosition(x, y);
	m_text.setPosition(x + 7, y + 7);
}

void TextInput::setSize(u16 width, u16 height) {
	m_rectText.setSize(width, height);
}

void TextInput::onEvent(const SDL_Event &event) {
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && !m_content.empty()) {
		m_content.erase(m_content.begin() + m_content.length() - 1);
		gk::AudioPlayer::playSound("sound-keyboard");

		m_text.setText(m_content + "|");
	}

  	if (event.type == SDL_TEXTINPUT) {
		std::string text = event.text.text;
		for (char c : text) {
			if (isprint(c) && (!m_characterLimit || m_content.size() < m_characterLimit)) {
				m_content += c;
				gk::AudioPlayer::playSound("sound-keyboard");
			}

			m_text.setText(m_content + "|");
		}
	}
}

void TextInput::draw(gk::RenderTarget &target, gk::RenderStates states) const {
	target.draw(m_rectText, states);
	target.draw(m_text, states);
}

