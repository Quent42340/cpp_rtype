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

#include <gk/core/SDLHeaders.hpp>
#include <gk/graphics/RectangleShape.hpp>
#include <gk/graphics/Text.hpp>

class TextInput : public gk::IDrawable, public gk::Transformable {
	public:
		TextInput();

		void onEvent(const SDL_Event &event);

		const std::string &content() const { return m_content; }

		gk::Vector2f getSize() const { return m_rectText.getSize(); }

		void setPosition(float x, float y);
		void setSize(u16 width, u16 height);
		void setCharacterLimit(u16 characterLimit) { m_characterLimit = characterLimit; }

	private:
		void draw(gk::RenderTarget &target, gk::RenderStates states) const override;

		gk::RectangleShape m_rectText;

		gk::Text m_text;
		std::string m_content;

		u16 m_characterLimit = 0;
};

#endif /* TEXTINPUT_HPP_*/
