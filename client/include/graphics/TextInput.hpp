/*
 * =====================================================================================
 *
 *       Filename:  TextInput.hpp
 *
 *    Description:
 *
 *        Created:  22/01/2018 14:35:10
 *
 *         Author:  Dylan Prinsaud, dylan.prinsaud@epitech.eu
 *
 * =====================================================================================
 */
#ifndef TEXTINPUT_HPP_
#define TEXTINPUT_HPP_

#include <SFML/Graphics.hpp>

#include "IntTypes.hpp"

class TextInput : public sf::Drawable, public sf::Transformable {
	public:
		TextInput();

		void onEvent(sf::Event &event);

		const std::string &content() const { return m_content; }

		sf::Vector2f getSize() const { return m_rectText.getSize(); }

		void setPosition(float x, float y);
		void setSize(u16 width, u16 height);
		void setCharacterLimit(u16 characterLimit) { m_characterLimit = characterLimit; }

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		sf::RectangleShape m_rectText;

		sf::Text m_text;
		std::string m_content;

		u16 m_characterLimit = 0;
};

#endif /* TEXTINPUT_HPP_*/
