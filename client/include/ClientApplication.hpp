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
		ClientApplication(int argc, char **argv);

		void init();

		void handleEvents();

		int run();
		void mainLoop();

	private:
		sf::RenderWindow m_window;

		ApplicationStateStack m_stateStack;

		GameClock m_clock;

		KeyboardHandler m_keyboardHandler;

		Network m_network;

		ResourceHandler m_resourceHandler;
};

#endif // CLIENTAPPLICATION_HPP_
