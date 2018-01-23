/*
 * =====================================================================================
 *
 *       Filename:  KeyboardHandler.hpp
 *
 *    Description:
 *
 *        Created:  17/01/2018 19:14:03
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef KEYBOARDHANDLER_HPP_
#define KEYBOARDHANDLER_HPP_

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "InputHandler.hpp"

class KeyboardHandler : public InputHandler {
	public:
		void resetState();

		void updateState(const sf::Event &event);

		bool isKeyPressed(GameKey key) override;
		bool isKeyPressedOnce(GameKey key) override;

	private:
		std::map<GameKey, sf::Keyboard::Key> m_keys{
			{GameKey::Left,     sf::Keyboard::Left},
			{GameKey::Right,    sf::Keyboard::Right},
			{GameKey::Up,       sf::Keyboard::Up},
			{GameKey::Down,     sf::Keyboard::Down},

			{GameKey::A,        sf::Keyboard::Space},
			{GameKey::B,        sf::Keyboard::Y},

			{GameKey::Start,    sf::Keyboard::Return},
			{GameKey::Select,   sf::Keyboard::BackSpace}
		};
};

#endif // KEYBOARDHANDLER_HPP_
