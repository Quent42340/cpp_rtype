/*
 * =====================================================================================
 *
 *       Filename:  ClientApplication.hpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 00:30:35
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef CLIENTAPPLICATION_HPP_
#define CLIENTAPPLICATION_HPP_

#include <SFML/Graphics.hpp>

#include "ApplicationStateStack.hpp"
#include "GameClock.hpp"
#include "KeyboardHandler.hpp"
#include "Network.hpp"
#include "ResourceHandler.hpp"

class ClientApplication {
	public:
		void init();

		void handleEvents();

		int run();
		void mainLoop();

		const static u16 screenWidth = 864;
		const static u16 screenHeight = 486;

	private:
		sf::RenderWindow m_window;

		ApplicationStateStack m_stateStack;

		GameClock m_clock;

		KeyboardHandler m_keyboardHandler;

		Network m_network{4243};

		ResourceHandler m_resourceHandler;
};

#endif // CLIENTAPPLICATION_HPP_
