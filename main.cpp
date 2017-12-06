#include <iostream>
#include <cstring>
#include <sys/socket.h>     // socket
#include <netinet/in.h>     // ?
#include <arpa/inet.h>      // inet_aton
#include <thread>

#include "socket.h"

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

	my::Socket socketA{};

	try {
		socketA = my::Socket(server_address);
		socketA.run(dest_address);
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

