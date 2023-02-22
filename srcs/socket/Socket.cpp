/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:02:53 by conobi            #+#    #+#             */
/*   Updated: 2023/02/22 02:08:51 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket(const int domain, const int type, const int protocol)
	: _sock_fd(-1), _epoll_fd(-1) {
	int setsock_ret;
	int opt = 1;

	cout << FBLU("Socket initialization constructor called.") << endl;

	bzero(&(this->_sock_addr), sizeof(this->_sock_addr));

	if ((this->_sock_fd = socket(domain, type, protocol) >= 0)) {
		setsock_ret = setsockopt(this->_sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt,
								 sizeof(int));
		if (setsock_ret < 0) {
			// todo: throw error on socket settings initialization
		}
		this->_type = type;
		this->_protocol = protocol;
		this->_sock_addr.sin_family = domain;
	} else {
		// todo: throw error on socket creation
	}
}

Socket::~Socket() {
	if (this->_epoll_fd >= 0)
		close(this->_epoll_fd);
	if (this->_sock_fd >= 0)
		close(this->_sock_fd);

	cout << FYEL("Socket destructor called.") << endl;
}

void Socket::bindAddress(const in_addr_t addr, const uint port) {
	this->_sock_addr.sin_addr.s_addr = addr;
	this->_sock_addr.sin_port = htons(port);
	if (bind(this->_sock_fd, (const struct sockaddr *)&this->_sock_addr,
			 sizeof(this->_sock_addr)) < 0) {
		// todo: throw error on binding. Give a specific error on already used
		// port
	}
}

void Socket::bindAddress(const uint port) {
	this->bindAddress(INADDR_ANY, port);
}

int Socket::createEpollFd() {
	if ((this->_epoll_fd = epoll_create(255)) < 0) {
		// todo: throw error on epoll creation
	}
	return (this->_epoll_fd);
}

void Socket::listenTo(int max_connections) {
	if (listen(this->_sock_fd, max_connections) < 0) {
		// todo: throw error on listen bad execution
	}
}

int Socket::sock_fd() {
	if (this->_sock_fd < 0) {
		// todo: throw undefined sock_fd
	}
	return (this->_sock_fd);
}

int Socket::epoll_fd() {
	if (this->_epoll_fd < 0) {
		// todo: throw undefined epoll_fd
	}
	return (this->_epoll_fd);
}

// Todo: add some getters to other public values (address/port)

int Socket::epollAdd(int epoll_fd, int fd, uint32_t events) {
	struct epoll_event ep_event;

	bzero(&ep_event, sizeof(ep_event));
	ep_event.events = events;
	ep_event.data.fd = fd;

	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ep_event) < 0)
		return -1;
	return 0;
}

int Socket::epollDelete(int epoll_fd, int fd) {
	if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL) < 0)
		return -1;
	return 0;
}
