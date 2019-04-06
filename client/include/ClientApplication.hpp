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

#include <gk/core/CoreApplication.hpp>
#include <gk/core/input/KeyboardHandler.hpp>

class ClientApplication : public gk::CoreApplication {
	public:
		ClientApplication(int argc, char **argv) : CoreApplication(argc, argv) {}

		void init();

	private:
		void onEvent(const sf::Event &event);

		gk::KeyboardHandler m_keyboardHandler;
};

#endif // CLIENTAPPLICATION_HPP_
