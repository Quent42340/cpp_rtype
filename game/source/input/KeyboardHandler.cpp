/*
 * =====================================================================================
 *
 *       Filename:  KeyboardHandler.cpp
 *
 *    Description:
 *
 *        Created:  11/02/2015 15:49:47
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "KeyboardHandler.hpp"

void KeyboardHandler::updateState(const SDL_Event &event) {
	for(auto &it : m_keys) {
		if(event.type == SDL_KEYDOWN && event.key.keysym.sym == it.second) {
			m_keysPressed[it.first] = true;
		}

		if (event.type == SDL_KEYUP && event.key.keysym.sym == it.second) {
			m_keysPressed[it.first] = false;
		}
	}
}

