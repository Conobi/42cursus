/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:02:53 by conobi            #+#    #+#             */
/*   Updated: 2023/02/22 19:19:09 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

#include <cstring>
#include <sstream>

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
			stringstream err_msg;
			err_msg << "Could not init socket settings. setsockopt(): "
					<< strerror(errno);
			throw SocketCreationException(err_msg.str());
		}
		this->_type = type;
		this->_protocol = protocol;
		this->_sock_addr.sin_family = domain;
	} else {
		stringstream err_msg;
		err_msg << "Could not create socket. socket(): " << strerror(errno);
		throw SocketCreationException(err_msg.str());
	}
}

Socket::~Socket() throw() {
	if (this->_epoll_fd >= 0) {
		if (close(this->_epoll_fd) < 0) {
			stringstream err_msg;
			err_msg << "Could not close the epoll_fd. close(): "
					<< strerror(errno);
			throw SystemException(err_msg.str());
		}
	}
	if (this->_sock_fd >= 0) {
		if (close(this->_sock_fd) < 0) {
			stringstream err_msg;
			err_msg << "Could not close the sock_fd. close(): "
					<< strerror(errno);
			throw SystemException(err_msg.str());
		}
	}

	cout << FYEL("Socket destructor called.") << endl;
}

void Socket::bindAddress(const in_addr_t addr, const uint port) {
	this->_sock_addr.sin_addr.s_addr = addr;
	this->_sock_addr.sin_port = htons(port);
	if (bind(this->_sock_fd, (const struct sockaddr *)&this->_sock_addr,
			 sizeof(this->_sock_addr)) < 0) {
		if (errno == EADDRINUSE)
			throw BindException("Port already in use.");
		else {
			stringstream err_msg;
			err_msg << "Could not bind the socket socket. bind(): "
					<< strerror(errno);
			throw BindException(err_msg.str());
		}
	}
}

void Socket::bindAddress(const uint port) {
	this->bindAddress(INADDR_ANY, port);
}

int Socket::createEpollFd() {
	if ((this->_epoll_fd = epoll_create(255)) < 0) {
		stringstream err_msg;
		err_msg << "Could not create the epoll_fd. epoll_create(): "
				<< strerror(errno);
		throw SystemException(err_msg.str());
	}
	return (this->_epoll_fd);
}

void Socket::listenTo(int max_connections) {
	if (listen(this->_sock_fd, max_connections) < 0) {
		stringstream err_msg;
		err_msg << "listen(): " << strerror(errno);
		throw SystemException(err_msg.str());
	}
}

int Socket::sock_fd() {
	if (this->_sock_fd < 0) {
		// throw UndefinedFdException("The socket file descriptor is
		// undefined.");
	}
	return (this->_sock_fd);
}

int Socket::epoll_fd() {
	if (this->_epoll_fd < 0) {
		// throw UndefinedFdException("The epoll file descriptor is
		// undefined.");
	}
	return (this->_epoll_fd);
}

// Todo: add some getters to other public values (address/port)

void Socket::epollAdd(int epoll_fd, int fd, uint32_t events) {
	struct epoll_event ep_event;

	bzero(&ep_event, sizeof(ep_event));
	ep_event.events = events;
	ep_event.data.fd = fd;

	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ep_event) < 0) {
		stringstream err_msg;
		err_msg << "epoll_ctl(... EPOLL_CTL_ADD...): " << strerror(errno);
		throw SystemException(err_msg.str());
	}
}

void Socket::epollDelete(int epoll_fd, int fd) {
	if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL) < 0) {
		stringstream err_msg;
		err_msg << "epoll_ctl(... EPOLL_CTL_DEL...): " << strerror(errno);
		throw SystemException(err_msg.str());
	}
}
