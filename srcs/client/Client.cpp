/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:26:11 by conobi            #+#    #+#             */
/*   Updated: 2023/03/14 16:18:42 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::~Client() {
	delete &this->_logger;
}

Client::Client(const Client &val)
	: _authStatus(UNAUTHENTICATED), _logger(*(new Logger(val._logger))) {
	*this = val;
}

Client &Client::operator=(const Client &rhs) {
	if (this != &rhs) {
		this->_fd = rhs.fd();
		this->_ip = rhs.ip();
		this->_port = rhs.port();
		this->_nick = rhs.nick();
		this->_username = rhs.username();
		this->_authStatus = rhs.authStatus();
	}
	return *this;
}

Client::Client(int fd, string ip, unsigned int port)
	: _fd(fd),
	  _ip(ip),
	  _port(port),
	  _logger(*(new Logger("Client [" + Utils::valToString(fd) + "]"))) {
}

int Client::fd() const {
	return this->_fd;
}

string Client::ip() const {
	return this->_ip;
}

ushort Client::port() const {
	return this->_port;
}

string &Client::nick() {
	return this->_nick;
}

const string &Client::nick() const {
	return this->_nick;
}

string &Client::username() {
	return this->_username;
}

const string &Client::username() const {
	return this->_username;
}

status &Client::authStatus() {
	return this->_authStatus;
}

const status &Client::authStatus() const {
	return this->_authStatus;
}

void Client::registerUser(Server &server) {
	if (this->_authStatus == REGISTERED) {
		this->_logger.info("User already registered", false);
		this->sendMessage(Output(server, this, "462", ":You may not reregister"));
		return;
	}
	if (this->_authStatus == UNAUTHENTICATED) {
		this->_logger.log("User not authenticated", false);
		this->sendMessage(Output(server, this, "451", ":You have not registered"));
		return;
	}
	this->_authStatus = REGISTERED;
	this->sendMessage(Output(server, this, "001 " + this->_nick, ":Welcome to the Internet Relay Network " + this->_nick));
	// todo: maybe add some server info
	this->sendMessage(Output(server, this, "002 " + this->_nick, ":Your host is " + server.ip() + ", running version 0.1"));
	this->sendMessage(Output(server, this, "003 " + this->_nick, ":This server was created 2023-02-21"));
	this->sendMessage(Output(server, this, "004 " + this->_nick, server.ip() + " 0.1 oOr RO"));
	this->_logger.info("User registered", false);
}

bool Client::operator==(const int &fd) const {
	return this->fd() == fd;
}

bool Client::operator==(const Client &client) const {
	return this->fd() == client.fd();
}

bool Client::operator==(const string &nick) const {
	return this->nick() == nick;
}

bool Client::operator<(const Client &rhs) const {
	return this->fd() < rhs.fd();
}
