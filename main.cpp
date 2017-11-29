//
// Created by Francisco Cruz on 28/11/2017.
//

#include <iostream>
#include <cerrno>
#include <cstring>
#include <system_error>
#include <pthread.h>
#include <exception>

#include "socket.h"

int main (int argc, char** argv)
{
	char ip[10] = "127.0.0.1";

	// Creación del socket
	try {
		my::Socket sock(ip, 0);
	}
	catch (std::bad_alloc& e) {
		std::cerr << program_invocation_name << ": memoria insuficiente\n";
		return 1;
	}
	catch (std::system_error& e) {
		std::cerr << program_invocation_name << ": " << e.what() << '\n';
		return 2;
	}

	return 0;
}