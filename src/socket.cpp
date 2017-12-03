#include "../include/socket.h"

my::Socket::Socket(const sockaddr_in &address) : address_(address)
{
	int fd_ = socket(AF_INET, SOCK_DGRAM, 0);

	if (fd_ < 0) {
		// throw an exception if the socket can't be generated
		throw std::system_error(errno, std::system_category());
	}

	int result = bind(fd_, reinterpret_cast<const sockaddr *>(&address_), sizeof(address_));

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

int my::Socket::send_to(const my::Message &message, sockaddr_in &address)
{
	ssize_t result = sendto(fd_, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&address), sizeof(address));

	if (result < 0) {
		// throw an exception if the text cannot be sent
		throw std::system_error(errno, std::system_category());
}

	return 0;
}

int my::Socket::recv_from(sockaddr_in &remote_address)
{
	Message message{};
	socklen_t src_len = sizeof(remote_address);
	ssize_t result = recvfrom(fd_, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&remote_address), &src_len);

	if (result < 0) {
		// throw an exception if the text couldn't be received
		throw std::system_error(errno, std::system_category());
	}

	char* remote_ip = inet_ntoa(remote_address.sin_addr);
	int remote_port = ntohs(remote_address.sin_port);
	message.text[2048] = '\0';
	std::cout << "El sistema " << remote_ip << ":" << remote_port
			  << " envió el mensaje '" << message.text << "'\n";

	return 0;
}

void my::Socket::run(sockaddr_in remote_address)
{
	while (1) {
		char str[size_message];
		std::cout << "Inserte su mensaje: ";
		std::cin >> str;
		str[size_message] = '\0';
		Message msg{};
		strncpy(msg.text, str, size_message);
		send_to(msg, remote_address);
		recv_from(remote_address);
	}
}

int my::Socket::get_fd() const
{
	return fd_;
}

const sockaddr_in &my::Socket::get_address() const
{
	return address_;
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
