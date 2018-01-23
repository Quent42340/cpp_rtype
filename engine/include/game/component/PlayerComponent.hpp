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
		PlayerComponent(u16 clientId) : m_clientId(clientId) {}

		u16 clientId() const { return m_clientId; }

	private:
		u16 m_clientId;
};

#endif // PLAYERCOMPONENT_HPP_
