/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:44 by conobi            #+#    #+#             */
/*   Updated: 2023/02/24 02:46:18 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const ushort port, const string password)
	: _logger(*(new Logger("Server"))),
	  _socket(*(new Socket(AF_INET, SOCK_STREAM, 0))),
	  _stop(false),
	  _port(port),
	  _password(password) {
	// Create socket connection with ipv4 protocol
	this->_socket.bindAddress(port);
	this->_socket.createEpollFd();
	this->_socket.listenTo(9999);
	Socket::epollAdd(this->_socket.epoll_fd(), this->_socket.sock_fd(),
					 EPOLLIN | EPOLLPRI);
	this->_startServer();
}

Server::~Server() {
	_logger.log("Stopping the server...", false);
	Socket::epollDelete(this->_socket.epoll_fd(), this->_socket.sock_fd());
	delete &(this->_socket);
	delete &this->_logger;
}

void Server::_startServer() {
	const int maxevents = 32;
	struct epoll_event events[maxevents];

	bzero(&events, sizeof(events));
	_logger.log("Starting to listen on " + this->_socket.ip() + ":" +
					Utils::valToString(this->_socket.port()),
				false);

	while (!this->_stop) {
		this->_epollHandler(3200, events, maxevents);
	}
}
