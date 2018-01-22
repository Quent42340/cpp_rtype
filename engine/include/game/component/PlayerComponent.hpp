/*
 * =====================================================================================
 *
 *       Filename:  PlayerComponent.hpp
 *
 *    Description:
 *
 *        Created:  22/01/2018 21:13:24
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef PLAYERCOMPONENT_HPP_
#define PLAYERCOMPONENT_HPP_

#include "IntTypes.hpp"

class PlayerComponent {
	public:
		PlayerComponent(u16 clientPort) : m_clientPort(clientPort) {}

		u16 clientPort() const { return m_clientPort; }

	private:
		u16 m_clientPort;
};

#endif // PLAYERCOMPONENT_HPP_
