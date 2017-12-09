#ifndef CHAT_SSOO_17_SOCKET_H
#define CHAT_SSOO_17_SOCKET_H

#include <sys/socket.h>     // socket
#include <sys/types.h>      // uint_32
#include <netinet/in.h>     // sockaddr:in
#include <arpa/inet.h>      // inet_aton
#include <cerrno>
#include <cstring>
#include <iostream>
#include <thread>
#include <pthread.h>
#include <cxxabi.h>
#include <unistd.h>
#include <atomic>

#include "utilities.h"

namespace my
{
struct Message;

/**
 * The Socket class is responsible for creating, destroying and
 * using the sockets for sending and receiving messages.
 */
class Socket
{
	int fd_;        			///< Socket file descriptor
	static int total_;        	///< Number of instances of the class
	int id_;        			///< Unique identifier of the instance

public:

	/**
	 * Default constructor.
	 * Initialize the socket without any value, only taking into account the number of the instance of the object.
	 */
	Socket();

	/**
	 * Move constructor
	 * @param rhs it's the right hand side element from which data is extracted and invalidated.
	 */
	Socket(Socket&& rhs) noexcept;

	/**
	 * Create a socket with a specific address.
	 * @param server_address contains the IP address and port to be assigned to the socket
	 */
	explicit Socket(const sockaddr_in& server_address);


	Socket(const Socket&) = delete;
	Socket operator=(const Socket&) = delete;

	/**
	 * @brief Default destructor. Close the socket file descriptor.
	 */
	~Socket() noexcept;

	/**
	 * @brief Send a my::Message struct to a specific address and port
	 * @param message it's a my::Message type, containing the message and the user who send it.
	 * @param dest_address contains the IP address and the port to which messages should be transmitted.
	 */
	void send_to(const sockaddr_in& dest_address, const Message& message) const;


	/**
	 * @brief Receive a message of type my::Message
	 * @param recv_address contains the address and the port from the issuing user
	 * @param message contains the message among other data about the issuing user
	 */
	void recv_from(sockaddr_in& recv_address, Message& message) const;


	/**
	 * Move assignment operator
	 * @param rhs
	 * @return
	 */
	Socket& operator=(Socket&& rhs) noexcept;

	int get_fd() const;

	void set_fd(const int& fd);

};
}

#endif //CHAT_SSOO_17_SOCKET_H
