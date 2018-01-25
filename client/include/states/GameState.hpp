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

#include <SFML/Graphics/Text.hpp>
#include <SFML/Network/IpAddress.hpp>

#include "ApplicationState.hpp"
#include "Client.hpp"
#include "Image.hpp"
#include "Scene.hpp"

class GameState : public ApplicationState {
	public:
		GameState(const sf::IpAddress &serverAddress, u16 serverPort = 4243);

		void onEvent(sf::Event &event) override;

		void update() override;

	private:
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

		Client m_client;

		Image m_background{"background-space"};
		Image m_background2{"background-space"};

		Scene m_scene;

		sf::Text m_readyText;

		bool m_hasGameStarted = false;
};

#endif // GAMESTATE_HPP_
