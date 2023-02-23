/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_epoll.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:44:25 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 04:14:26 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <stdexcept>

#include "Server.hpp"

void Server::_epollHandler() {
	int ep_value;
	int timeout = 3000;
	int maxevents = 32;
	string cin_line;
	struct epoll_event events[maxevents];

	ep_value = epoll_wait(this->_socket.epoll_fd(), events, maxevents, timeout);

	if (!std::getline(std::cin, cin_line)) {
		_logger.log("CTRL+D detected. Stopping the server...", false);
		this->_stop = true;
	}

	// No events within [timeout] ms
	if (ep_value == 0) {
		return;
	}

	if (ep_value < 0) {
		if (errno == EINTR) {
			_logger.info("epoll_wait() has been interrupted", false);
			return;
		}
		stringstream err_msg;
		err_msg << "epoll_wait(): " << strerror(errno);
		throw runtime_error(err_msg.str());
	}
}

void Server::_epollFdHandler(const int ready_fds, struct epoll_event events[]) {
	for (int i = 0; i < ready_fds; i++) {
		int client_fd = events[i].data.fd;

		// If a new client try to connect to us
		if (client_fd == this->_socket.sock_fd()) {
			this->_acceptNewClient(client_fd);

			continue;
		}
		this->_handleClientEvent(client_fd, events[i].events);
	}
}
