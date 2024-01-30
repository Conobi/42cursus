/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_epoll.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 03:44:25 by conobi            #+#    #+#             */
/*   Updated: 2023/03/21 17:03:10 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::_epollHandler(const int timeout, struct epoll_event events[],
						   const int maxevents) {
	int ep_value;

	ep_value = epoll_wait(this->_socket.epoll_fd(), events, maxevents, timeout);

	if (ep_value == 0) {
		return;
	}

	if (ep_value < 0) {
		if (errno == EINTR) {
			_logger.info("epoll_wait() has been interrupted", false);
			return;
		}
		throw runtime_error("epoll_wait(): " +
							Utils::valToString(strerror(errno)));
	}

	this->_epollFdHandler(ep_value, events);
}

void Server::_epollFdHandler(const int ready_fds, struct epoll_event events[]) {
	for (int i = 0; i < ready_fds; i++) {
		int client_fd = events[i].data.fd;

		// If a new client try to connect to us
		if (client_fd == this->_socket.sock_fd()) {
			this->_acceptNewClient();

			continue;
		}
		this->_handleClientEvent(client_fd, events[i].events);
	}
}
