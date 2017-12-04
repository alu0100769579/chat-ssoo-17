#ifndef CHAT_SSOO_17_MESSAGE_H
#define CHAT_SSOO_17_MESSAGE_H

#include <string>
namespace my
{
static const size_t max_size_message  = 2048; ///< max length of the message
static const int 	max_size_username = 25;	 ///< max lenght of the username
/**
 * Message is a simple struct that gives support to the messages the sockets receive and send
 */
struct Message
{
	char username[max_size_username];
	char text[max_size_message]; 			///< content of the message
	std::string str;
	size_t size_text;
	size_t size_user;
};
}

#endif //CHAT_SSOO_17_MESSAGE_H
