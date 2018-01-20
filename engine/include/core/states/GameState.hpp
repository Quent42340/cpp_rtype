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
#include "Image.hpp"
#include "Scene.hpp"
#include "Timer.hpp"

class GameState : public ApplicationState {
	public:
		GameState();

		void update() override;

		// static sf::View view;

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		Image m_background{"backgrounds-space"};
		Scene m_scene;
		Timer m_spawnTimer;
};

#endif // GAMESTATE_HPP_
