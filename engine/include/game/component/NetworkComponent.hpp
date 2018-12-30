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

#include <gk/core/Timer.hpp>

class NetworkComponent {
	public:
		NetworkComponent() {
			timer.start();
		}

		gk::Timer timer{true};
		bool hasSpawned = false;

		u32 lastUpdateTimestamp = 0;
};

#endif // NETWORKCOMPONENT_HPP_
