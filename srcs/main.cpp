/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 02:53:01 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 18:14:36 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"
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

	return (intPort);
}

int main(int ac, char **av) {
	Logger &_logger = *(new Logger("Main"));

	if (ac != 3) {
		_logger.err("usage: ./ircserv  <port> <password>");
		delete &_logger;
		return (1);
	}
	try {
		int port = parsePort(av[1]);

		Server(port, av[2]);
	} catch (const exception &e) {
		_logger.err(e.what());
		delete &_logger;
		return (1);
	}
	delete &_logger;
	return (0);
}
