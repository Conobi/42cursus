/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:44 by conobi            #+#    #+#             */
/*   Updated: 2023/02/21 19:29:46 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int Server::_guard(int code, const char *process) {
	if (code == -1) {
		cerr << FRED("ERROR: ");
		perror(process);
		if (this->_tcp_fd >= 0)
			close(this->_tcp_fd);
		exit(EXIT_FAILURE);
	}
	return code;
}

Server::Server(const int port, const string password)
	: _stop(false), _port(port), _tcp_fd(-1), _password(password) {
	int opt = 1;

	cout << FGRN("Server listening on port ") << port << endl;

	// Create socket connection with ipv4 protocol
	this->createSocket(AF_INET, SOCK_STREAM, 0);

	// guard(fcntl(this->_sockfd, F_SETFL, O_NONBLOCK), "fcntl");

	_guard(
		setsockopt(this->_tcp_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)),
		"setsockopt");

	// Bind socket to port
	this->setSocketAddr(port);

	this->bindSocket(this->_tcp_fd);

	this->_eventHandler();
}

Server::~Server() {
}

int Server::createSocket(const int domain, const int type, const int protocol) {
	this->_tcp_fd = _guard(socket(domain, type, protocol), "socket");
	cout << FGRN("Socket created: ") << this->_tcp_fd << endl;
	return this->_tcp_fd;
}

void Server::setSocketAddr(const int port) {
	sockaddr_in sock_addr;

	bzero(&sock_addr, sizeof(sock_addr));
	// todo: replace AF_INET
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = INADDR_ANY;
	sock_addr.sin_port = htons(port);

	this->_sock_addr = sock_addr;
}

void Server::bindSocket(const int socket) {
	if (bind(socket, (const struct sockaddr *)&this->_sock_addr,
			 sizeof(this->_sock_addr)) < 0) {
		if (errno == EADDRINUSE) {
			perror(FRED("ERROR: ") "Address already in use");
			exit(EXIT_FAILURE);
		}
		perror(FRED("ERROR: ") "bind");
		exit(EXIT_FAILURE);
	}
}

void Server::_eventHandler() {
	int ep_fd;

	struct epoll_event ep_event;

	ep_fd = _guard(epoll_create(255), "epoll_create");

	bzero(&ep_event, sizeof(ep_event));
	ep_event.events = EPOLLIN | EPOLLPRI;
	ep_event.data.fd = this->_tcp_fd;
	_guard(epoll_ctl(ep_fd, EPOLL_CTL_ADD, this->_tcp_fd, &ep_event),
		   "epoll_ctl(EPOLL_CTL_ADD)");
	_eventLoop(ep_fd);
	close(ep_fd);
}

void Server::_eventLoop(int ep_fd) {
	int timeout = 3000; /* in milliseconds */
	int maxevents = 32;
	int epoll_ret;
	struct epoll_event events[maxevents];

	while (!this->_stop) {
		epoll_ret = epoll_wait(ep_fd, events, maxevents, timeout);

		if (epoll_ret == 0) {
			cout << "No event within " << timeout << "ms" << endl;
			continue;
		}

		if (epoll_ret == -1) {
			if (errno == EINTR) {
				cout << "The server was interrupted" << endl;
				continue;
			} else {
				close(ep_fd);
				_guard(-1, "epoll_wait()");
			}
		}

		for (int i = 0; i < epoll_ret; i++) {
			int fd = events[i].data.fd;

			if (fd == this->_tcp_fd) {
				/*
				 * A new client is connecting to us...
				 */
				if (_accept_new_client(fd) < 0) {
					_guard(-1,
						   "Server::_accept_new_client()");	 // Todo: Handling
															 // directly in the
															 // function
				}
				continue;
			}

			/*
			 * We have event(s) from client, let's call `recv()` to read it.
			 */
			_handle_client_event(fd, events[i].events);
		}
	}
}
