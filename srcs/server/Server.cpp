/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:44 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 02:51:06 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>

#include "Socket.hpp"

Server::Server(const int port, const string password)
	: _socket(*(new Socket(AF_INET, SOCK_STREAM, 0))),
	  _stop(false),
	  _port(port),
	  _password(password),
	  _logger(*(new Logger("Server"))) {
	// Create socket connection with ipv4 protocol
	this->_socket.bindAddress(port);
	this->_socket.createEpollFd();
	Socket::epollAdd(this->_socket.epoll_fd(), this->_socket.sock_fd(),
					 EPOLLIN | EPOLLPRI);
	this->_eventLoop();
}

Server::~Server() {
	_logger.log("Stopping the server...", false);
	delete &this->_logger;
	Socket::epollDelete(this->_socket.epoll_fd(), this->_socket.sock_fd());
	delete &(this->_socket);
}

void Server::_eventLoop() {
	stringstream ss;
	string cin_line;

	ss << "Starting to listen on " << this->_socket.ip() << ":"
	   << this->_socket.port();
	_logger.log(ss.str(), false);

	while (!this->_stop) {
		if (!std::getline(std::cin, cin_line)) {
			_logger.log("CTRL+D detected. Stopping the server...", false);
			this->_stop = true;
		}
	}
}
