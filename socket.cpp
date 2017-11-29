//
// Created by Francisco Cruz on 28/11/2017.
//


#include "socket.h"

my::Socket::Socket(const std::string &address, const uint16_t &puerto)
{
	fd_ = socket(AF_INET, SOCK_DGRAM, 0);

	if (fd_ < 0) {
		std::cerr << "no se pudo crear el socket: " << std::strerror(errno) << '\n';
		throw std::system_error(errno, std::system_category());
	}

	sockaddr_in local_address{};
	inet_aton(address.c_str(), &local_address.sin_addr);

	local_address.sin_port   = htons(puerto);
	local_address.sin_family = AF_INET;

	int b = bind(fd_, reinterpret_cast<const sockaddr*>(&local_address), local_address.sin_addr.s_addr);

	if (b < 0) {
		std::cerr << "falló bind: " << std::strerror(errno) << '\n';
		throw std::system_error(errno, std::system_category());
	}
}

void my::Socket::send_to(const Message &message, const std::string &address, const uint16_t& port)
{
	sockaddr_in remote_address{};

	remote_address.sin_family = AF_INET;
	remote_address.sin_port   = htons(port);

	inet_aton(address.c_str(), &remote_address.sin_addr);
	std::string msg (message.text);

	ssize_t result = sendto(fd_, &message, sizeof(message), 0,
	                    reinterpret_cast<const sockaddr*>(&remote_address),
	                    sizeof(remote_address));

	if (result < 0) {
		std::cerr << "falló sendto: " << std::strerror(errno) << '\n';
		throw std::system_error(errno, std::system_category());
	}
}
