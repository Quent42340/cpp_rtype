/**
 * File              : server.cpp
 * Author            : Dorian Turba <dorian.turba@gmail.com>
 * Date              : 14.01.2018
 * Last Modified Date: 18.01.2018
 * Last Modified By  : Dorian Turba <dorian.turba@gmail.com>
 */
#include <cstring>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <thread>
#include <mutex>

#define PORT 4242

void	print(std::string msg)
{
	std::cout << msg << std::endl;
	return (void());
}

void	send_message(int sckt, sockaddr_in *to)
{
	std::cout << "entrer un mot :" << std::endl;
	while (1)
	{
		std::string	data;
		int		result;

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
		//		else
		//			break;
	}
}

void	receiv(int sckt)
{
	while (1)
	{
		sockaddr_in	from;
		socklen_t	fromlen = sizeof(from);
		char	buff[1500] = { 0 };
		int	result;
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

int	test()
{
	int	sckt;
	int 	result;
	sockaddr_in	to;
	unsigned short	port_dest;

	sckt = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	to.sin_addr.s_addr = htonl(INADDR_ANY);
	to.sin_port = htons(PORT);
	to.sin_family = AF_INET;
	result = bind(sckt, (sockaddr*)&to, sizeof(to));
	if (result != 0)
	{
		std::cerr << "bind error: " << strerror(errno) << std::endl;
		print(std::to_string(result));
		return (1);
	}

	std::cout << "port local dest ?";
	std::cin >> port_dest;

	sockaddr_in	dst;

	if (inet_pton(AF_INET, "127.0.0.1", &dst.sin_addr) <= 0)
	{
		print("impossible de déterminer l'adresse");
		return(1);
	}
	dst.sin_family = AF_INET;
	dst.sin_port = htons(port_dest);

	std::thread t1 (send_message, sckt, &dst);
	std::thread t2 (receiv, sckt);
	t1.join();
	t2.join();
	return (sckt);
}

int	main()
{
	test();
	return (0);
}
