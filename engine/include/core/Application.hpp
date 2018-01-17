/*
 * =====================================================================================
 *
 *       Filename:  Application.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 18:52:06
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <SFML/Graphics.hpp>

#include "GameClock.hpp"
#include "KeyboardHandler.hpp"
#include "ResourceHandler.hpp"

class Application {
	public:
		Application();

		void handleEvents();

		void run();

		static bool quit;

		const static u16 screenWidth = 640;
		const static u16 screenHeight = 480;

	private:
		sf::RenderWindow m_window;

		GameClock m_clock;

		KeyboardHandler m_keyboardHandler;

		ResourceHandler m_resourceHandler;
};

#endif // APPLICATION_HPP_
