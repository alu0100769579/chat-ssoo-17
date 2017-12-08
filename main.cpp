#include <iostream>
#include <cstring>
#include <sys/socket.h>     // socket
#include <netinet/in.h>     // ?
#include <arpa/inet.h>      // inet_aton
#include <thread>
#include <atomic>

#include "socket.h"
#include "utilities.h"

int main ()
{
	int port;

	std::cout << "Local port: \n";
	std::cin >> port;

	sockaddr_in server_address {};
	server_address.sin_family      = AF_INET;            						// IP Protocol
	server_address.sin_port        = htons(static_cast<uint16_t >(port));       // user choose port
	server_address.sin_addr.s_addr = htonl(INADDR_ANY); 						// 0.0.0.0 IP

	std::cout << "Remote port\n";
	std::cin >> port;

	sockaddr_in dest_address {};
	dest_address.sin_family      = AF_INET;            						// IP Protocol
	dest_address.sin_port        = htons(static_cast<uint16_t >(port));    	// User choose port
	dest_address.sin_addr.s_addr = htonl(INADDR_ANY); 						// 0.0.0.0 IP

	sockaddr_in recv_address {};
	my::Socket socketA;
	std::atomic_bool quit(false);

	try {
		socketA = my::Socket(server_address);
		std::thread recv(&my::receiver, std::ref(socketA), std::ref(recv_address), std::ref(quit));
		std::thread send(&my::sender, std::ref(socketA), std::ref(dest_address), std::ref(quit));
		send.join();
		if (quit) // TODO: realmente el quit no es necesario no?
			my::request_cancellation(recv);
		recv.join();
	}
	catch (const std::bad_alloc& e) {
		std::cerr << program_invocation_short_name << ": CRITICAL: " << e.what() << '\n';
		return errno;
	}
	catch (const std::system_error& e) {
		std::cerr << program_invocation_short_name << ": CRITICAL: " << e.what() << '\n';
		return errno;
	}
	catch (...) {
		std::cerr << program_invocation_short_name << ": CRITICAL: " << strerror(errno) << '\n';
		return errno;
	}

	return 0;
}

