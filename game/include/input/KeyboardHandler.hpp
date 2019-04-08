/*
 * =====================================================================================
 *
 *       Filename:  KeyboardHandler.hpp
 *
 *    Description:
 *
 *        Created:  11/02/2015 15:49:54
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef KEYBOARDHANDLER_HPP_
#define KEYBOARDHANDLER_HPP_

#include <gk/core/input/KeyboardHandler.hpp>

class KeyboardHandler : public gk::KeyboardHandler {
	public:
		KeyboardHandler() : gk::KeyboardHandler() {}

		void updateState(const SDL_Event &event);
};

#endif // KEYBOARDHANDLER_HPP_
