/*
 * =====================================================================================
 *
 *       Filename:  TitleScreenState.hpp
 *
 *    Description:
 *
 *        Created:  19/01/2018 22:04:30
 *
 *         Author:  Dylan Prinsaud, dylan.prinsaud@epitech.eu
 *
 * =====================================================================================
 */
#ifndef TITLESCREENSTATE_HPP_
#define TITLESCREENSTATE_HPP_

#include <gk/core/ApplicationState.hpp>

#include "Button.hpp"

class TitleScreenState : public gk::ApplicationState {
	public:
		TitleScreenState();

		void onEvent(const sf::Event &event) override;

		void update() override;

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		gk::Image m_background{"texture-background-space"};

		Button m_play{"Play"};
		Button m_exit{"Exit"};

		sf::Text m_rtype;
};

#endif // TITLESCREENSTATE_HPP_


