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

#include <algorithm>
#include <string>
#include <vector>

#include "IntTypes.hpp"

struct Client {
	u16 port;
};

class ServerInfo {
	public:
		void addClient(u16 port) {
			auto it = std::find_if(m_clients.begin(), m_clients.end(), [port] (Client &client) { return client.port == port; });
			if (it == m_clients.end()) {
				m_clients.emplace_back(Client{port});
			}
		}

		const std::vector<Client> &clients() const { return m_clients; }

		static ServerInfo &getInstance() {
			static ServerInfo instance;
			return instance;
		}

	private:
		ServerInfo() = default;

		std::vector<Client> m_clients;
};

#endif // SERVERINFO_HPP_
