/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:44 by conobi            #+#    #+#             */
/*   Updated: 2023/03/21 23:16:03 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const ushort port, const string password)
	: _logger(*(new Logger("Server"))),
	  _socket(*(new Socket(AF_INET, SOCK_STREAM, 0))),
	  _stop(false),
	  _port(port),
	  _password(password),
	  _creation_date("") {
	time_t now = time(0);
	char *dt = ctime(&now);

	if (dt) {
		dt[strlen(dt) - 1] = '\0';
	}
	this->_creation_date = dt;

	// Create socket connection with ipv4 protocol
	this->_socket.bindAddress(port);
	this->_socket.createEpollFd();
	this->_socket.listenTo(MAX_USERS);
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
	this->_commands["PRIVMSG"] = &Command::privmsg;
	this->_commands["MODE"] = &Command::mode;
	this->_commands["KICK"] = &Command::kick;
	this->_commands["NAMES"] = &Command::names;
	this->_commands["INVITE"] = &Command::invite;
	this->_commands["CAP"] = &Command::cap;
	this->_commands["TOPIC"] = &Command::topic;

	this->_startServer();
}

Server::~Server() {
	_logger.log("Stopping the server...", false);
	Socket::epollDelete(this->_socket.epoll_fd(), this->_socket.sock_fd());
	delete &(this->_socket);
	delete &this->_logger;
}

void Server::_startServer() {
	struct epoll_event events[MAX_EVENTS];

	bzero(&events, sizeof(events));
	_logger.log("Starting to listen on " + this->_socket.ip() + ":" +
					Utils::valToString(this->_socket.port()),
				false);

	while (!this->_stop) {
		this->_epollHandler(3200, events, MAX_EVENTS);
	}
}

const string Server::ip() const {
	string ip = _socket.ip();
	return ip;
};
