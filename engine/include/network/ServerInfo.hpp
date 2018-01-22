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
#include <vector>

#include "Exception.hpp"
#include "NetworkInputHandler.hpp"

struct Client {
	u16 port;
	NetworkInputHandler inputHandler;
};

class ServerInfo {
	public:
		void addClient(u16 port) {
			auto it = std::find_if(m_clients.begin(), m_clients.end(), [port] (Client &client) { return client.port == port; });
			if (it == m_clients.end())
				m_clients.emplace_back(Client{port, {}});
		}

		void removeClient(u16 port) {
			auto it = std::find_if(m_clients.begin(), m_clients.end(), [port] (Client &client) { return client.port == port; });
			if (it != m_clients.end())
				m_clients.erase(it);
		}

		Client &getClient(u16 port) {
			auto it = std::find_if(m_clients.begin(), m_clients.end(), [port] (Client &client) { return client.port == port; });
			if (it == m_clients.end())
				throw EXCEPTION("No client connected on port ", port);

			return *it;
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
