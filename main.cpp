#include <iostream>
#include <cstring>
#include <sys/socket.h>     // socket
#include <netinet/in.h>     // ?
#include <arpa/inet.h>      // inet_aton
#include <pthread.h>
#include <thread>
#include <mutex>
#include <regex>
#include <cstdlib>

#include "socket.h"

static const int ip_len   = 16;
static const int port_len = 5;

int main (int argc, char** argv)
{
//	╔══════════════════════╗
//	║ Local socket address ║
//	╚══════════════════════╝
	sockaddr_in local_address{};

	local_address.sin_family      = AF_INET;            // TCP/IP Protocol
	local_address.sin_port        = htons(0);           // OS choose port
	local_address.sin_addr.s_addr = htonl(INADDR_ANY);  // 0.0.0.0 IP TODO: la IP inicial debe ser INADDR_ANY para local?

	// Show local IP
//	std::cout << "Dirección IP: " << inet_ntoa(local_address.sin_addr) << '\n'
//			  << "Puerto: " 	  << ntohs(local_address.sin_port) 	   << "\n\n";

//	╔═══════════════════════════════════════════╗
//	║ Ask for data of the remote socket to user ║ TODO: esto se hace así?
//	╚═══════════════════════════════════════════╝
	char port[port_len];
	char ip_addr[ip_len];

	std::cout << "Inserte la dirección IP: ";
	std::cin >> ip_addr;

	std::cout << "Inserte el puerto: ";
	std::cin >> port;

//	╔═══════════════════════════╗
//	║ Check the ip and the port ║ TODO: de verdad tengo que hacer esto?
//	╚═══════════════════════════╝
	std::regex regex_ip_addr(R"([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3})");
	if (!std::regex_match(ip_addr, regex_ip_addr)) {
		std::cerr << "Introduced IP address is not correct.";
		std::exit(1);
	}

	std::regex regex_port(R"([0-9]{1,5})");
	if (!std::regex_match(port, regex_port)) {
		std::cerr << "Introduced port is not correct.";
		std::exit(1);
	}

//	╔═══════════════════════╗
//	║ Remote socket address ║
//	╚═══════════════════════╝
	sockaddr_in remote_address{};

	remote_address.sin_family = AF_INET;            		// TCP/IP Protocol
	remote_address.sin_port   = htons(std::stoi(port));		// Assign port defined by user
	inet_aton(ip_addr, &remote_address.sin_addr);			// IP conversion

//	╔═══════════════════════╗
//	║ Socket initialization ║
//	╚═══════════════════════╝
	try { // TODO: cómo gestiono los sockets si estos se ciñen al ámbito del try?
		my::Socket local  (local_address);
		my::Socket remote (remote_address);
	}
	catch (std::bad_alloc& e) {
		std::cerr << program_invocation_short_name << ": CRITICAL: " << e.what() << '\n';
		return errno;
	}
	catch (std::system_error& e) {
		std::cerr << program_invocation_short_name << ": CRITICAL: " << e.what() << '\n';
		return errno;
	}
	// TODO: el destructor no está siendo llamado por alguna razón que desconozco
	return 0;
}
