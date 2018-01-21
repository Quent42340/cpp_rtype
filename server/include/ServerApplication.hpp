/*
 * =====================================================================================
 *
 *       Filename:  ServerApplication.hpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 00:22:13
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SERVERAPPLICATION_HPP_
#define SERVERAPPLICATION_HPP_

#include <SFML/Network.hpp>

class ServerApplication {
	public:
		ServerApplication();

		void run();

	private:
		sf::UdpSocket m_socket;
};

#endif // SERVERAPPLICATION_HPP_
