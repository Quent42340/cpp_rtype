/*
 * =====================================================================================
 *
 *       Filename:  NetworkCommandHandler.hpp
 *
 *    Description:
 *
 *        Created:  22/01/2018 14:37:44
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef NETWORKCOMMANDHANDLER_HPP_
#define NETWORKCOMMANDHANDLER_HPP_

#include "ApplicationStateStack.hpp"
#include "Scene.hpp"

class NetworkCommandHandler {
	public:
		static void disconnect();

		static void sendKey(u32 key, bool isPressed);

		static void update(ApplicationStateStack &stateStack, Scene &scene);
};

#endif // NETWORKCOMMANDHANDLER_HPP_
