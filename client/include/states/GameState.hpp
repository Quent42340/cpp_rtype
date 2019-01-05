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

#include <SFML/Network/IpAddress.hpp>

#include <gk/core/ApplicationState.hpp>
#include <gk/graphics/Image.hpp>
#include <gk/graphics/Text.hpp>
#include <gk/scene/Scene.hpp>

#include "Client.hpp"

class GameState : public gk::ApplicationState {
	public:
		GameState(const sf::IpAddress &serverAddress, u16 serverPort = 4242);

		void onEvent(const SDL_Event &event) override;

		void update() override;

	private:
		void draw(gk::RenderTarget &target, gk::RenderStates states) const override;

		Client m_client;

		gk::Image m_background{"background-space"};
		gk::Image m_background2{"background-space"};

		gk::Scene m_scene;

		gk::Text m_readyText;

		bool m_hasGameStarted = false;
};

#endif // GAMESTATE_HPP_
