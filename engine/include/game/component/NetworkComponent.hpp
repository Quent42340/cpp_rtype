/*
 * =====================================================================================
 *
 *       Filename:  NetworkComponent.hpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 13:43:20
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef NETWORKCOMPONENT_HPP_
#define NETWORKCOMPONENT_HPP_

#include "Timer.hpp"

class NetworkComponent {
	public:
		NetworkComponent() {
			timer.start();
		}

		Timer timer{true};
		bool hasSpawned = false;
};

#endif // NETWORKCOMPONENT_HPP_
