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

#include "ApplicationState.hpp"
#include "Button.hpp"

class GameEndState : public ApplicationState {
	public:
		GameEndState(bool isWinner);

		void onEvent(sf::Event &event) override;

		void update() override;

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		sf::Text m_text;

		Image m_background{"background-space"};

		Button m_leave{"Leave"};
		Button m_exit{"Exit"};
};

#endif /* GAMEENDSTATE_HPP */

