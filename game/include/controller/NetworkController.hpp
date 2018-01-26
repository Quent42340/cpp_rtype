/*
 * =====================================================================================
 *
 *       Filename:  NetworkController.hpp
 *
 *    Description:
 *
 *        Created:  26/01/2018 01:21:34
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef NETWORKCONTROLLER_HPP_
#define NETWORKCONTROLLER_HPP_

#include <SFML/Network/UdpSocket.hpp>

#include "AbstractController.hpp"

class NetworkController : public AbstractController {
	public:
		NetworkController(sf::UdpSocket &socket) : m_socket(socket) {}

		void update(SceneObject &object) override;

	private:
		sf::UdpSocket &m_socket;
};

#endif // NETWORKCONTROLLER_HPP_
