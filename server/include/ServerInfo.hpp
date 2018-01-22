/*
 * =====================================================================================
 *
 *       Filename:  ServerInfo.hpp
 *
 *    Description:
 *
 *        Created:  22/01/2018 19:03:23
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SERVERINFO_HPP_
#define SERVERINFO_HPP_

#include <array>
#include <string>

#include "IntTypes.hpp"

struct Client {
	u16 port;
};

class ServerInfo {
	public:
		void addClient(u8 id, u16 port) { m_clients[id] = {port}; }

	private:
		std::array<Client, 4> m_clients;
};

#endif // SERVERINFO_HPP_
