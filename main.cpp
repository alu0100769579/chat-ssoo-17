#include <iostream>
#include <cstring>
#include <sys/socket.h>     // socket
#include <netinet/in.h>     // ?
#include <arpa/inet.h>      // inet_aton
#include <regex>
#include <thread>

#include "socket.h"


int main ()
{
	int port;

	std::cout << "Puerto local: \n";
	std::cin >> port;

	sockaddr_in server_address {};
	server_address.sin_family      = AF_INET;            	// TCP/IP Protocol
	server_address.sin_port        = htons(port);       	// user choose port
	server_address.sin_addr.s_addr = htonl(INADDR_ANY); 		// 0.0.0.0 IP

	std::cout << "Puerto remoto\n";
	std::cin >> port;

	sockaddr_in dest_address {};
	dest_address.sin_family      = AF_INET;            	// TCP/IP Protocol
	dest_address.sin_port        = htons(port);       	// user choose port
	dest_address.sin_addr.s_addr = htonl(INADDR_ANY); 		// 0.0.0.0 IP

	try { // TODO: cómo gestiono los sockets si estos se ciñen al ámbito del try?
		my::Socket sckt (server_address);
		sckt.run(dest_address);
	}
	catch (std::bad_alloc& e) {
		std::cerr << program_invocation_short_name << ": CRITICAL: " << e.what() << '\n';
		return errno;
	}
	catch (std::system_error& e) {
		std::cerr << program_invocation_short_name << ": CRITICAL: " << e.what() << '\n';
		return errno;
	}
	catch (...) {
		std::cerr << program_invocation_short_name << ": CRITICAL: " << strerror(errno) << '\n';
		return errno;
	}

	return 0;
}

