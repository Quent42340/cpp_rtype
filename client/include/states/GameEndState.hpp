/*
 * =====================================================================================
 *
 *       Filename:  GameEndState.hpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 08:20:17
 *
 *         Author:  Dylan Prinsaud, dylan.prinsaud@epitech.eu
 *
 * =====================================================================================
 */
#ifndef GAMEENDSTATE_HPP_
#define GAMEENDSTATE_HPP_

#include <gk/core/ApplicationState.hpp>

#include "Button.hpp"

class GameEndState : public gk::ApplicationState {
	public:
		GameEndState(bool isWinner);

		void onEvent(const SDL_Event &event) override;

		void update() override;

	private:
		void draw(gk::RenderTarget &target, gk::RenderStates states) const override;

		gk::Text m_text;

		gk::Image m_background{"texture-background-space"};

		Button m_leave{"Leave"};
		Button m_exit{"Exit"};
};

#endif /* GAMEENDSTATE_HPP */

