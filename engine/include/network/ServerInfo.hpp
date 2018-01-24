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
#include <memory>
#include <vector>

#include <SFML/Network.hpp>

#include "Exception.hpp"
#include "NetworkInputHandler.hpp"

struct Client {
	Client(u16 _id, u16 _port, const std::shared_ptr<sf::TcpSocket> &socket)
		: id(_id), port(_port), tcpSocket(socket) {}

	u16 id;
	u16 port;
	bool isReady = false;
	std::shared_ptr<sf::TcpSocket> tcpSocket;
	NetworkInputHandler inputHandler;
};

class ServerInfo {
	public:
		Client &addClient(u16 port, const std::shared_ptr<sf::TcpSocket> &socket) {
			static u16 clientCount = 0;
			m_clients.emplace_back(clientCount++, port, socket);
			return m_clients.back();
		}

		void removeClient(u16 id) {
			auto it = std::find_if(m_clients.begin(), m_clients.end(), [id] (Client &client) { return client.id == id; });
			if (it != m_clients.end())
				m_clients.erase(it);
		}

		Client *getClient(u16 id) {
			auto it = std::find_if(m_clients.begin(), m_clients.end(), [id] (Client &client) { return client.id == id; });
			if (it == m_clients.end())
				return nullptr;

			return &*it;
		}

		std::vector<Client> &clients() { return m_clients; }
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
