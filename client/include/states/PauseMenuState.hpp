/*
 * =====================================================================================
 *
 *       Filename:  PauseMenuState.hpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 06:44:36
 *
 *         Author:  Dylan Prinsaud, dylan.prinsaud@epitech.eu
 *
 * =====================================================================================
 */
#ifndef PAUSEMENUSTATE_HPP_
#define PAUSEMENUSTATE_HPP_

#include <gk/core/ApplicationState.hpp>

#include "Button.hpp"

class PauseMenuState : public gk::ApplicationState {
	public:
		PauseMenuState();

		void onEvent(const sf::Event &event) override;

		void update() override;

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		gk::Image m_background{"texture-background-space"};

		sf::Text m_text;

		Button m_resume{"Resume"};
		Button m_leave{"Leave"};
		Button m_exit{"Exit"};
};

#endif /* PAUSEMENUSTATE_HPP */

