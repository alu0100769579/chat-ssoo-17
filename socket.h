//
// Created by Francisco Cruz on 28/11/2017.
//

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
 * Socket Class provide an easy way to handle sockets, send and receive messages.
 */
class Socket
{
	int fd_;        ///< Socket file descriptor
	static int total_;        ///<
	int id_;        ///<
	static const int max_size_msg = 2048;    ///<

public:

	/**
	 * Default constructor.
	 *
	 * Initialize the socket without any value, only taking into account the number of the instance of the object.
	 */
	Socket();


	/**
	 * Move constructor
	 * @param rhs
	 */
	Socket(Socket&& rhs) noexcept;

	/**
	 * Create a socket with an explicit address.
	 * @param address assigns an address and a port to the socket.
	 */
	explicit Socket(const sockaddr_in& address);


	Socket(const Socket&) = delete;
	Socket operator=(const Socket&) = delete;

	/**
	 * Default destructor.
	 *
	 * Close the file descriptor of socket.
	 */
	~Socket() noexcept;

	/** TODO: documentar
	 *
	 * @param message
	 * @param address
	 * @return
	 */
	void send_to(const sockaddr_in& address, const Message& message) const;


	/** TODO: documentar
	 *
	 * @param message
	 * @param recv_address
	 * @return
	 */
	void recv_from(sockaddr_in& recv_address, Message& message) const;


	/**
	 *
	 * @param rhs
	 * @return
	 */
	Socket& operator=(Socket&& rhs) noexcept;

	int get_fd() const;

	void set_fd(const int& fd);

};
}

#endif //CHAT_SSOO_17_SOCKET_H
