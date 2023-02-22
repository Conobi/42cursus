/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:44 by conobi            #+#    #+#             */
/*   Updated: 2023/02/22 02:26:45 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>

Server::Server(const int port, const string password)
	: _socket(Socket(AF_INET, SOCK_STREAM, 0)),
	  _stop(false),
	  _port(port),
	  _password(password) {
	cout << FBLU("Server constructor called.") << endl;

	// Create socket connection with ipv4 protocol
	this->_socket.bindAddress(port);
	this->_socket.createEpollFd();
	Socket::epollAdd(this->_socket.epoll_fd(), this->_socket.sock_fd(),
					 EPOLLIN | EPOLLPRI);
	this->_eventLoop();
}

Server::~Server() {
	cout << FYEL("Server destructor called.") << endl;
}

void Server::_eventLoop() {
}
