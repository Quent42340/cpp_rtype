/*
 * =====================================================================================
 *
 *       Filename:  GameState.hpp
 *
 *    Description:
 *
 *        Created:  18/01/2018 02:44:55
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <SFML/Graphics/View.hpp>

#include "ApplicationState.hpp"
#include "Scene.hpp"

class GameState : public ApplicationState {
	public:
		GameState();

		void update() override;

		static sf::View view;

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		Scene m_scene;
};

#endif // GAMESTATE_HPP_
