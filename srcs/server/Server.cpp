/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:44 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 01:59:07 by conobi           ###   ########lyon.fr   */
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
	  _password(password) {
	log(FBLU("Server constructor called."), true);

	// Create socket connection with ipv4 protocol
	this->_socket.bindAddress(port);
	this->_socket.createEpollFd();
	Socket::epollAdd(this->_socket.epoll_fd(), this->_socket.sock_fd(),
					 EPOLLIN | EPOLLPRI);
	this->_eventLoop();
}

Server::~Server() {
	log(FYEL("Server destructor called."), true);
	log("Stopping the server...", false);
	Socket::epollDelete(this->_socket.epoll_fd(), this->_socket.sock_fd());
	delete &(this->_socket);
}

void Server::_eventLoop() {
	stringstream ss;
	string cin_line;

	ss << "Starting to listen on " << this->_socket.ip() << ":"
	   << this->_socket.port();
	log(ss.str(), false);

	while (!this->_stop) {
		if (!std::getline(std::cin, cin_line)) {
			log("CTRL+D detected. Stopping the server...", false);
			this->_stop = true;
		}
	}
}
