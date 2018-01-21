/*
 * =====================================================================================
 *
 *       Filename:  ServerApplication.cpp
 *
 *    Description:
 *
 *        Created:  21/01/2018 00:22:52
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "ServerApplication.hpp"
#include "TestEntityFactory.hpp"

ServerApplication::ServerApplication() {
	m_socket.bind(4242);
}

void ServerApplication::run() {
	while (true) {
		sf::Packet packet;
		sf::IpAddress senderAddress;
		u16 senderPort;
		m_socket.receive(packet, senderAddress, senderPort);

		std::cout << "Message received from: " << senderAddress << ":" << senderPort << std::endl;
		std::cout << "Content: ";
		std::string str;
		u32 keyCode;
		packet >> str >> keyCode;
		std::cout << str << keyCode << std::endl;
	}
}

