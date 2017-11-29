//
// Created by Francisco Cruz on 28/11/2017.
//

#ifndef CHAT_SSOO_17_SOCKET_H
#define CHAT_SSOO_17_SOCKET_H

#include <sys/socket.h>     // socket
#include <sys/types.h>      // uint_32
#include <netinet/in.h>     // ?
#include <arpa/inet.h>      // inet_aton
#include <cerrno>
#include <cstring>
#include <iostream>


#include "message.h"

namespace my
{
class Socket
{
	int fd_;

public:
	Socket() = default;
	Socket(const std::string &address, const uint16_t &puerto);
	~Socket() = default;
	void send_to(const Message &message, const std::string &address, const uint16_t &port);
};
}

#endif //CHAT_SSOO_17_SOCKET_H
