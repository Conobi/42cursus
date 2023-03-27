/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 02:53:01 by conobi            #+#    #+#             */
/*   Updated: 2023/03/27 16:39:12 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
#include "Server.hpp"
#include "irc.hpp"

static int parsePort(const string port) {
	int intPort;

	if (port.empty()) {
		throw out_of_range("No port has been specified");
	}

	for (int i = 0; port[i]; i++) {
		if (port[i] < '0' || port[i] > '9') {
			throw invalid_argument("Port must a number");
		}
	}

	istringstream(port) >> intPort;

	if (intPort < 1 || intPort > 65535) {
		throw out_of_range("Port must be in 1-65535");
	}

	return (intPort);
}

static void signal_callback_handler(int signum) {
	(void)signum;
	throw runtime_error("Ctrl+C command given.");
}

// Same main but that delete the server with its destructor

int main(int ac, char **av) {
	Logger _logger = Logger("Main");
	Server *server = NULL;

	if (ac != 3) {
		_logger.err("usage: ./ircserv  <port> <password>");
		return (1);
	}
	try {
		int port = parsePort(av[1]);

		if (!*av[2]) {
			throw out_of_range("Password cannot be unspecified");
		}
		signal(SIGINT, signal_callback_handler);
		server = new Server(port, av[2]);
	} catch (const exception &e) {
		_logger.err(e.what());
		delete server;
		return (1);
	}
	delete server;
	return (0);
}
