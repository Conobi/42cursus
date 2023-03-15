/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:44 by conobi            #+#    #+#             */
/*   Updated: 2023/03/15 03:34:04 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include "Command.hpp"

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

	// Init commands
	this->_commands["NICK"] = &Command::nick;
	this->_commands["USER"] = &Command::user;
	this->_commands["PING"] = &Command::ping;
	this->_commands["PASS"] = &Command::pass;
	this->_commands["QUIT"] = &Command::quit;
	this->_commands["JOIN"] = &Command::join;
	this->_commands["PART"] = &Command::part;

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

const string Server::ip() const {
	string ip = _socket.ip();
	return ip;
};
