#include "utilities.h"

void my::sender(const Socket& sock, const sockaddr_in& dest_address, std::atomic_bool& quit)
{
	// Avoid \n in the first iteration
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (!quit) {
		std::string str;
		std::getline(std::cin, str); 	// TODO: How do I keep the input prompt always down?

		if (str == "\\quit")
			quit = true;

		my::Message message {};

		memset(&message, 0, sizeof message);
		size_t sz = str.copy(message.text, str.size());
		message.text[sz] = '\0';
		message.size_text = sz;

		sock.send_to(dest_address, message);
	}
}

void my::receiver(const Socket& sock, sockaddr_in& recv_address, std::atomic_bool& quit)
{
	try {
		while (!quit) {
			my::Message message {};
			sock.recv_from(recv_address, message);

			message.text[message.size_text] = '\0';
			std::cout << inet_ntoa(recv_address.sin_addr) << ":" << ntohs(recv_address.sin_port);
			std::cout << " -> ";

			std:: cout << ( strcmp(message.text, "\\quit") == 0 ?
							"\033[1;33mEl usuario ha abandonado\033[0m" : message.text )
					   << '\n';
		}
	}
	catch (abi::__forced_unwind& e) {
		std::cout << "abi::__forced_unwind catched" << std::endl;
		throw;
	}
	catch (...) {
		std::cout << "some other thing catched in receiver" << std::endl;
		throw;
	}
}

int my::request_cancellation(std::thread& thread)
{
	return pthread_cancel(thread.native_handle());
}
