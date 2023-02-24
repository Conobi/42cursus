/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:02:53 by conobi            #+#    #+#             */
/*   Updated: 2023/02/24 02:43:26 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

Socket::Socket(const int domain, const int type, const int protocol)
	: _port(0),
	  _sock_fd(-1),
	  _epoll_fd(-1),
	  _ip(""),
	  _logger(*new Logger("Socket")) {
	int setsock_ret;
	int opt = 1;

	bzero(&(this->_sock_addr), sizeof(this->_sock_addr));

	this->_sock_fd = socket(domain, type, protocol);
	if (this->_sock_fd >= 0) {
		setsock_ret = setsockopt(this->_sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt,
								 sizeof(int));
		if (setsock_ret < 0) {
			throw runtime_error(
				"Could not init socket settings. setsockopt(): " +
				Utils::valToString(strerror(errno)));
		}
		this->_type = type;
		this->_protocol = protocol;
		this->_sock_addr.sin_family = domain;

	} else {
		throw runtime_error("Could not create socket. socket(): " +
							Utils::valToString(strerror(errno)));
	}
}

Socket::~Socket() throw() {
	if (this->_epoll_fd >= 0) {
		if (close(this->_epoll_fd) < 0) {
			throw runtime_error("Could not close the epoll_fd. close(): " +
								Utils::valToString(strerror(errno)));
		}
	}
	if (this->_sock_fd >= 0) {
		if (close(this->_sock_fd) < 0) {
			throw runtime_error("Could not close the sock_fd. close(): " +
								Utils::valToString(strerror(errno)));
		}
	}
	delete &this->_logger;
}

void Socket::bindAddress(const in_addr_t addr, const ushort port) {
	int bind_ret;

	this->_sock_addr.sin_addr.s_addr = addr;
	this->_sock_addr.sin_port = htons(port);
	this->_ip = inet_ntoa(this->_sock_addr.sin_addr);
	this->_port = port;

	bind_ret = bind(this->_sock_fd, (const struct sockaddr *)&this->_sock_addr,
					sizeof(this->_sock_addr));

	if (bind_ret < 0) {
		if (errno == EADDRINUSE) {
			throw runtime_error(this->_ip + ":" +
								Utils::valToString(this->_port) +
								" is already in use.");
		} else {
			throw runtime_error(
				"Could not bind the socket to " + this->_ip + ":" +
				Utils::valToString(this->_port) +
				". bind(): " + Utils::valToString(strerror(errno)));
		}
	}
}

void Socket::bindAddress(const uint port) {
	this->bindAddress(INADDR_ANY, port);
}

int Socket::createEpollFd() {
	if ((this->_epoll_fd = epoll_create(255)) < 0) {
		throw runtime_error("Could not create the epoll_fd. epoll_create(): " +
							Utils::valToString(strerror(errno)));
	}
	return (this->_epoll_fd);
}

void Socket::listenTo(int max_connections) {
	if (listen(this->_sock_fd, max_connections) < 0) {
		throw runtime_error("listen(): " + Utils::valToString(strerror(errno)));
	}
}

int Socket::sock_fd() const {
	if (this->_sock_fd < 0) {
		throw logic_error("The socket file descriptor is undefined.");
	}
	return (this->_sock_fd);
}

int Socket::epoll_fd() const {
	if (this->_epoll_fd < 0) {
		throw logic_error("The epoll file descriptor is undefined.");
	}
	return (this->_epoll_fd);
}

string Socket::ip() const {
	if (this->_ip.empty()) {
		throw logic_error("The socket ip is undefined.");
	}
	return (this->_ip);
}

ushort Socket::port() const {
	if (this->_port == 0) {
		throw logic_error("The socket port is undefined.");
	}
	return (this->_port);
}

void Socket::epollAdd(int epoll_fd, int fd, uint32_t events) {
	struct epoll_event ep_event;

	bzero(&ep_event, sizeof(ep_event));
	ep_event.events = events;
	ep_event.data.fd = fd;

	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ep_event) < 0) {
		throw runtime_error("epoll_ctl(... EPOLL_CTL_ADD...): " +
							Utils::valToString(strerror(errno)));
	}
}

void Socket::epollDelete(int epoll_fd, int fd) {
	if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL) < 0) {
		throw runtime_error("epoll_ctl(... EPOLL_CTL_DEL...): " +
							Utils::valToString(strerror(errno)));
	}
}
