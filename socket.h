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

#include "include/message.h"


namespace my
{

extern std::atomic<bool> quit__;	///< when true it stops the execution of the recv thread

/**
 * Socket Class provide an easy way to handle sockets, send and receive messages.
 */
class Socket
{
	int 		fd_;		///< Socket file descriptor
	static int 	total_;
	int 		id_;
public:

	Socket();

	/**
	 * Create a socket with an explicit address
	 * @param address assigns an address and a port to the socket
	 */
	explicit Socket(const sockaddr_in& address);


	/**
	 * Default destructor. Close the file descriptor of socket
	 */
	~Socket();

	/** TODO: documentar
	 *
	 * @param message
	 * @param address
	 * @return
	 */
	void send_to(const sockaddr_in &address);


	/** TODO: documentar
	 *
	 * @param message
	 * @param remote_address
	 * @return
	 */
	void recv_from(sockaddr_in remote_address);


	/**
	 *
	 * @param dest_address
	 */
	void run(sockaddr_in &dest_address);


	/**
	 *
	 * @param thread
	 */
	void request_cancellation(std::thread &thread);


	/**
	 *
	 * @param rhs
	 * @return
	 */
	Socket & operator=(Socket &&rhs) noexcept;

};
}

#endif //CHAT_SSOO_17_SOCKET_H
