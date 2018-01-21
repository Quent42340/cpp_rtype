/*
 * =====================================================================================
 *
 *       Filename:  NetworkInputHandler.hpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 10:54:01
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef NETWORKINPUTHANDLER_HPP_
#define NETWORKINPUTHANDLER_HPP_

#include <SFML/Window/Keyboard.hpp>

#include "InputHandler.hpp"

class NetworkInputHandler : public InputHandler {
	public:
		void setKeyPressed(u32 key, bool isPressed) {
			auto it = m_keys.find(key);
			if (it != m_keys.end())
				m_keysPressed[it->second] = isPressed;
		}

	private:
		std::map<u32, GameKey> m_keys{
			{sf::Keyboard::Left,      GameKey::Left},
			{sf::Keyboard::Right,     GameKey::Right},
			{sf::Keyboard::Up,        GameKey::Up},
			{sf::Keyboard::Down,      GameKey::Down},

			{sf::Keyboard::X,         GameKey::A},
			{sf::Keyboard::Y,         GameKey::B},

			{sf::Keyboard::Return,    GameKey::Start},
			{sf::Keyboard::BackSpace, GameKey::Select}
		};
};

#endif // NETWORKINPUTHANDLER_HPP_
