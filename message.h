#ifndef CHAT_SSOO_17_MESSAGE_H
#define CHAT_SSOO_17_MESSAGE_H

namespace my
{
static const size_t size_message = 2048; ///< max length of the message
/**
 * Message is a simple struct that gives support to the messages the sockets receive and send
 */
struct Message
{
	char message[size_message]; ///< content of the message
	//TODO: qué otros parámetros utilizamos?
};
}

#endif //CHAT_SSOO_17_MESSAGE_H
