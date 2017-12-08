#include "utilities.h"

void my::sender(const Socket& sock, const sockaddr_in& dest_address, std::atomic_bool& quit)
{
	while (!quit) {
		// TODO: como mantengo el prompt de entrada siempre abajo?
		// TODO: en la primera ejecución siempre envía un salto de línea
		std::string str;
		std::getline(std::cin, str);

		if (str == "\\quit") {
			quit = true;
		}

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

			std:: cout << ( strcmp(message.text, "\\quit") == 0 ? "\033[1;33mEl usuario ha abandonado\033[0m" : message.text ) << '\n';
		}
	}
	catch (abi::__forced_unwind& e) {
		std::cout << "abi::__forced_unwind catched\n";
		std::cout << std::flush;
		std::cin.get();
	}
}

void my::request_cancellation(std::thread& thread)
{
	int result = pthread_cancel(thread.native_handle());
	if (result != 0) {
		std::cerr << program_invocation_short_name << ": " << "Failure to cancel thread: " << result << '\n';
		throw;
	}
}
