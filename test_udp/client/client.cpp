/**
 * File              : client.cpp
 * Author            : Dorian Turba <dorian.turba@gmail.com>
 * Date              : 18.01.2018
 * Last Modified Date: 18.01.2018
 * Last Modified By  : Dorian Turba <dorian.turba@gmail.com>
 */
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <iostream>
#include <string>
#include <thread>

#define SERV_PORT 4242

void    print(std::string msg)
{
	std::cout << msg << std::endl;
	return (void());
}

void    send_message(int sckt, sockaddr_in *to)
{
	std::cout << "entrer un mot :" << std::endl;
	while (1)
	{
		std::string     data;
		int             result;

		std::getline(std::cin, data);
		if (!data.empty())
		{
			result = sendto(sckt, data.data(), static_cast<int>(data.length()), 0, (sockaddr*)to, sizeof(*to));
			if (result < 0)
			{
				print("erreur d'envoi");
				break;
			}
		}
		//              else
		//                      break;
	}
}

void    receiv(int sckt)
{
	while (1)
	{
		sockaddr_in     from;
		socklen_t       fromlen = sizeof(from);
		char    buff[1500] = { 0 };
		int     result;
		result = recvfrom(sckt, buff, 1499, 0, (sockaddr*)(&from), &fromlen);
		std::cout << "test co : " << from.sin_addr.s_addr  << std::endl;
		if (result <= 0)
		{
			print("erreur de reception");
			break;
		}
		std::cout << "Reçu : " << buff << std::endl;
	}
}

int main()
{

	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in	to;
	int	result;

	if (sock == 0)
	{
		std::cerr << "Erreur création socket" << strerror(errno) << std::endl;
		return (1);
	}
	to.sin_addr.s_addr = htonl(INADDR_ANY);
	to.sin_port = htons(0);
	to.sin_family = AF_INET;
	result = bind(sock, (sockaddr*)&to, sizeof(to));
	if (result != 0)
	{
		std::cerr << "bind error: " << strerror(errno) << std::endl;
		print(std::to_string(result));
		return (1);
	}

	sockaddr_in	serv_addr;
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		std::cout << "Impossible de déterminer l'adresse" << std::endl;
		return (1);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	std::thread t1 (send_message, sock, &serv_addr);
	std::thread t2 (receiv, sock);
	t1.join();
	t2.join();

	return 0;
}

