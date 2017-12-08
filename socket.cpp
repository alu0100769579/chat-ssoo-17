#include "socket.h"

int my::Socket::total_ = 0;

my::Socket::Socket()
{
	total_++;
	id_ = total_;
}

my::Socket::Socket(my::Socket&& rhs) noexcept
{
	total_++;
	id_ = total_;

	fd_ = rhs.fd_;
	rhs.fd_ = -1;
}

my::Socket::Socket(const sockaddr_in& address)
{
	total_++;
	id_ = total_;

	fd_ = socket(AF_INET, SOCK_DGRAM, 0);

	if (fd_ < 0) {
		// throw an exception if the socket can't be generated
		throw std::system_error(errno, std::system_category());
	}

	int result = bind(fd_, reinterpret_cast<const sockaddr*>(&address), sizeof(address));

	if (result < 0) {
		// throw an exception if the address assign cannot be produced
		throw std::system_error(errno, std::system_category());
	}
}

my::Socket::~Socket()
{
	close(fd_);
	std::cout << "Ejecución del destructor, instancia " << id_ << "\n";
}

int my::Socket::get_fd() const
{
	return fd_;
}

void my::Socket::set_fd(const int& fd)
{
	Socket::fd_ = fd;
}

void my::Socket::send_to(const sockaddr_in& address, const Message& message) const
{
	ssize_t result = sendto(fd_, &message, sizeof(message), 0,
							reinterpret_cast<const sockaddr*>(&address),
							sizeof(address));

	// throw an exception if the text cannot be sent
	if (result < 0)
		throw std::system_error(errno, std::system_category());
}

void my::Socket::recv_from(sockaddr_in& recv_address, Message& message) const
{
	socklen_t src_len = sizeof(recv_address);
	ssize_t result = recvfrom(fd_, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&recv_address), &src_len);

	// throw an exception if the text cannot be sent
	if (result < 0)
		throw std::system_error(errno, std::system_category());
}

my::Socket& my::Socket::operator=(Socket&& rhs) noexcept
{
	fd_ = rhs.fd_;
	rhs.fd_ = -1;
	return *this;
}
