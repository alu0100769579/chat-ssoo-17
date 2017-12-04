#include <thread>
#include "socket.h"

bool __quit__ = false;

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
	std::cout << "ejecución del destructor\n";
}

void my::Socket::send_to(const sockaddr_in &address)
{
	while (true) {
		// TODO: como mantengo el prompt de entrada siempre abajo?
		std::string str;
		std::getline(std::cin, str);

		if (str == "quit") {
			__quit__ = true;
			return;
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
		std::cout << inet_ntoa(address.sin_addr) <<":" << ntohs(address.sin_port);
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

int my::Socket::get_fd() const
{
	return fd_;
}



//my::Socket::Socket(const std::string &address, const uint16_t &puerto)
//{
//	fd_ = socket(AF_INET, SOCK_DGRAM, 0);
//
//	if (fd_ < 0) {
//		std::cerr << "no se pudo crear el socket: " << std::strerror(errno) << '\n';
//		throw std::system_error(errno, std::system_category());
//	}
//
//	sockaddr_in local_address{};
//
//	// TODO: local_address.sin_addr = inet_addr(address.c_str()); ¿por qué no?
//	inet_aton(address.c_str(), &local_address.sin_addr);
//	local_address.sin_port   = htons(puerto);
//	local_address.sin_family = AF_INET;
//
//	//TODO: porqué hacer un reinterpret_cast? y qué es s_addr?
//	int b = bind(fd_, reinterpret_cast<const sockaddr*>(&local_address), sizeof(local_address);
//
//
//	if (b < 0) {
//		std::cerr << "falló bind: " << std::strerror(errno) << '\n';
//		throw std::system_error(errno, std::system_category());
//	}
//}

//void my::Socket::send_to(const std::string& text, const std::string &address, const uint16_t &port)
//{
//	if (fd_ < 0) {
//		std::cerr << "Error";
//		exit(1);
//		// TODO: modificar a buenas prácticas
//	}
//
//	sockaddr_in remote_address{};
//
//	remote_address.sin_family = AF_INET;
//	remote_address.sin_port   = htons(port);
//
//	inet_aton(address.c_str(), &remote_address.sin_addr);
//
//	ssize_t result = sendto(fd_, &text, sizeof(text), 0, reinterpret_cast<const sockaddr *>(&remote_address),
//							sizeof(remote_address));
//
//	if (result < 0) {
//		std::cerr << "no se ha podido enviar el mensaje: " << std::strerror(errno) << '\n';
//		throw std::system_error(errno, std::system_category());
//	}
//}
