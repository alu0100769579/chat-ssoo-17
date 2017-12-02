#include "socket.h"

my::Socket::Socket(const sockaddr_in &address)
{
	int fd_ = socket(AF_INET, SOCK_DGRAM, 0);

	if (fd_ < 0) {
		// lanza una excepción si no se logra generar el socket
		throw std::system_error(errno, std::system_category());
	}

	int result = bind(fd_, reinterpret_cast<const sockaddr *>(&address), sizeof(address));

	if (result < 0) {
		// lanza una excepción si no se logra asignar la dirección al socket
		throw std::system_error(errno, std::system_category());
	}
}

my::Socket::~Socket()
{
	close(fd_sock);
	std::cout << "ejecución del destructor";
}

int my::Socket::send_to(const my::Message &message, const sockaddr_in &address)
{
	ssize_t result = sendto(fd_sock, &message, sizeof(message), 0, reinterpret_cast<const sockaddr*>(&address), sizeof(address));

	if (result < 0) {
		// lanza una excepción si no se logra enviar el mensaje
		throw std::system_error(errno, std::system_category(), "no se ha podido enviar el mensaje");
	}

	return 0;
}

int my::Socket::recv_from(my::Message &message, sockaddr_in &remote_address)
{
	socklen_t src_len = sizeof(remote_address);
	ssize_t result = recvfrom(fd_sock, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&remote_address), &src_len);

	if (result < 0) {
		// lanza una excepción si no se recibir enviar el mensaje
		throw std::system_error(errno, std::system_category(), "no se ha podido recibir el mensaje");
	}

	char* remote_ip = inet_ntoa(remote_address.sin_addr);
	int remote_port = ntohs(remote_address.sin_port);
	message.message[2048] = '\0';
	std::cout << "El sistema " << remote_ip << ":" << remote_port
			  << " envió el mensaje '" << message.message << "'\n";

	return 0;
}






//my::Socket::Socket(const std::string &address, const uint16_t &puerto)
//{
//	fd_sock = socket(AF_INET, SOCK_DGRAM, 0);
//
//	if (fd_sock < 0) {
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
//	int b = bind(fd_sock, reinterpret_cast<const sockaddr*>(&local_address), sizeof(local_address);
//
//
//	if (b < 0) {
//		std::cerr << "falló bind: " << std::strerror(errno) << '\n';
//		throw std::system_error(errno, std::system_category());
//	}
//}

//void my::Socket::send_to(const std::string& message, const std::string &address, const uint16_t &port)
//{
//	if (fd_sock < 0) {
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
//	ssize_t result = sendto(fd_sock, &message, sizeof(message), 0, reinterpret_cast<const sockaddr *>(&remote_address),
//							sizeof(remote_address));
//
//	if (result < 0) {
//		std::cerr << "no se ha podido enviar el mensaje: " << std::strerror(errno) << '\n';
//		throw std::system_error(errno, std::system_category());
//	}
//}
