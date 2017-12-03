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
#include <unistd.h>

#include "include/message.h"


namespace my
{
/**
 * Socket Class provide an easy way to handle sockets, send and receive messages.
 */
class Socket
{
	int 		fd_;	///< Socket file descriptor
	sockaddr_in address_;   ///< Local socket address

public:

	/**
	 * Create a socket with an explicit address
	 * @param address assigns an address and a port to the socket
	 */
	explicit Socket(const sockaddr_in& address);


	/**
	 * Default destructor. Close the file descriptor of socket
	 */
	~Socket();

	int get_fd() const;
	const sockaddr_in &get_address() const;


	/** TODO: documentar
	 *
	 * @param message
	 * @param address
	 * @return
	 */
	int send_to(const my::Message &message, sockaddr_in &address);


	/** TODO: documentar
	 *
	 * @param message
	 * @param remote_address
	 * @return
	 */
	int recv_from(sockaddr_in &remote_address);

	void run(sockaddr_in remote_address);
};
}

#endif //CHAT_SSOO_17_SOCKET_H
