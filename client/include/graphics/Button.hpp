/*
 * =====================================================================================
 *
 *       Filename:  Button.hpp
 *
 *    Description:
 *
 *        Created:  20/01/2018 23:51:59
 *
 *         Author:  Dylan Prinsaud, dylan.prinsaud@epitech.eu
 *
 * =====================================================================================
 */
#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include <gk/graphics/Image.hpp>

class Button : public sf::Drawable, public sf::Transformable {
	public:
		Button(const std::string &text);
		Button(const std::string &text, int posX, int posY);

		void onEvent(const sf::Event &event);

		void setPosition(int posX, int posY);

		void reset();

		bool isPressed() const { return m_hasReleased; }

		u16 width() { return m_image.width(); }
		u16 height() { return m_image.height(); }

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		bool m_isPressed = false;
		bool m_hasReleased = false;
		bool m_hasMouse = false;

		gk::Image m_image;

		sf::Text m_text;
};

#endif // BUTTON_HPP
