#include "Server.hpp"
#include "irc.hpp"

int parsePort(const string port) {
	int intPort;

	for (int i = 0; port[i]; i++) {
		if (port[i] < '0' || port[i] > '9') {
			throw invalid_argument("Port must a number");
		}
	}

	istringstream(port) >> intPort;

	if (intPort < 1 || intPort > 65535) {
		throw out_of_range("Port must be in 1-65535");
	}

	return intPort;
}

int main(int ac, char **av) {
	if (ac != 3) {
		cerr << FRED(BOLD("Error: usage: ./ircserv  <port> <password>"))
			 << endl;
		return 1;
	}
	try {
		int port = parsePort(av[1]);

		Server(port, av[2]);
	} catch (const exception &e) {
		cerr << FRED("ERROR: ") << e.what() << endl;
		return 1;
	}
	return 0;
}
