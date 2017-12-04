#include "socket.h"

std::atomic<bool> __quit__ (false);

my::Socket::Socket(const sockaddr_in &address)
{
	fd_ = socket(AF_INET, SOCK_DGRAM, 0);

	if (fd_ < 0) {
		// throw an exception if the socket can't be generated
		throw std::system_error(errno, std::system_category());
	}

	int result = bind(fd_, reinterpret_cast<const sockaddr *>(&address), sizeof(address));

	if (result < 0) {
		// throw an exception if the address assign cannot be produced
		throw std::system_error(errno, std::system_category());
	}
}

my::Socket::~Socket()
{
	close(fd_);
}

void my::Socket::send_to(const sockaddr_in &address)
{
	while (true) {
		// TODO: como mantengo el prompt de entrada siempre abajo?
		std::string str;
		std::getline(std::cin, str);

		if (str == "quit") {
			__quit__ = true;

		}

		char msg[2048];
		if (str.size() < 2048) {
			strcpy(msg, str.c_str());
		}

		ssize_t result = sendto(fd_, &msg, sizeof(msg), 0, reinterpret_cast<const sockaddr*>(&address), sizeof(address));

		if (result < 0) {
			// throw an exception if the text cannot be sent
			throw std::system_error(errno, std::system_category());
		}

		if (__quit__) return;
	}
}

void my::Socket::recv_from(sockaddr_in address)
{
	while (true) {
		if (__quit__) return;
		char msg[2048];

		socklen_t src_len = sizeof(address);
		ssize_t result = recvfrom(fd_, &msg, sizeof(msg), 0, reinterpret_cast<sockaddr*>(&address), &src_len);

		if (result < 0) {
			// throw an exception if the text cannot be sent
			throw std::system_error(errno, std::system_category());
		}

		msg[result] = '\0';
		std::cout << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port);
		std::cout << " -> " << (__quit__) ? "el usuario ha abandonado" : msg;
		std::cout << "\n";
	}
}

void my::Socket::run(sockaddr_in &dest_address)
{
	my::Message msg {};
	sockaddr_in remote_address {};

	std::thread send( [=] { send_to(dest_address); } );
	std::thread recv( [=] { recv_from(remote_address); } );

	send.join();
	recv.join();
}

void my::Socket::request_cancellation(thread &thread)
{
	int result = pthread_cancel(thread);
	if (result != 0)
		//handle_error_en(result, "pthread_cancel");
}
