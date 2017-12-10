/**
 * @file
 */

#ifndef CHAT_SSOO_17_UTILITIES_H
#define CHAT_SSOO_17_UTILITIES_H

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

/**
 * @namespace my
 * It's my personal namespace, for classes, constants, functions and whatever
 * I use in this source code.
 */
namespace my
{

static const std::size_t MAX_SZ_MSG  = 2048;	///< max length of the message
static const std::size_t MAX_SZ_USRNM = 25;	 	///< max lenght of the username

/**
 * Message contains the data of the sent and received messages
 */
struct Message
{
	char username[MAX_SZ_USRNM];	///< username that sent the message
	char text[MAX_SZ_MSG]; 			///< content of the message
	size_t size_user;				///< size of the username
	size_t size_text;				///< size of the message
};

// Explicit declaration of Socket for using it in the functions below
class Socket;

/**
 * Ask for user's input to send it to a concrete address.
 * @param sock it's the socket who support the communication
 * @param dest_address it's the destination address
 * @param quit it's a trigger that cancels the threads and exit the program
 */
void sender(const Socket& sock, const sockaddr_in& dest_address, std::atomic_bool& quit);

/**
 * Print in the screen the message received
 * @param sock it's the socket who support the communication
 * @param recv_address it's the sender address
 * @param quit it's a trigger that cancels the thread and exit the program
 */
void receiver(const Socket& sock, sockaddr_in& recv_address, std::atomic_bool& quit);

/**
 * Cancel the required thread using pthread_cancel() function (POSIX standard)
 * @param thread it's the thread wanted to end
 * @return the value of pthread_cancel()'s return value (0 = everything it's fine, another
 * value means that an error has occurred). See ISO/IEC/IEEE 9945:2009 (also IEEE 1003.1-2008)
 * p. 1572
 */
int request_cancellation(std::thread& thread);
}

#endif //CHAT_SSOO_17_UTILITIES_H
