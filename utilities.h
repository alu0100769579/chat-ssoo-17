#ifndef CHAT_SSOO_17_MESSAGE_H
#define CHAT_SSOO_17_MESSAGE_H

#include <string>
#include <thread>
#include <sys/socket.h>     // socket
#include <sys/types.h>      // uint_32
#include <netinet/in.h>     // sockaddr:in
#include <arpa/inet.h>      // inet_aton
#include <iostream>
#include <cstring>
#include <atomic>


#include "socket.h"

namespace my
{
static const std::size_t max_size_message  = 2048;	 ///< max length of the message
static const std::size_t max_size_username = 25;	 ///< max lenght of the username

/**
 * Message is a simple struct that gives support to the messages the sockets receive and send
 */
struct Message
{
	char username[max_size_username];
	char text[max_size_message]; 			///< content of the message
	size_t size_text;
	size_t size_user;
};
class Socket;
void sender(const Socket& sock, const sockaddr_in& dest_address, std::atomic_bool& quit);
void receiver(const Socket& sock, sockaddr_in& recv_address, std::atomic_bool& quit);
void request_cancellation(std::thread& thread);
}

#endif //CHAT_SSOO_17_MESSAGE_H
