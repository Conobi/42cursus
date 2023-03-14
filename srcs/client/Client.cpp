/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:26:11 by conobi            #+#    #+#             */
/*   Updated: 2023/03/14 14:43:35 by conobi           ###   ########lyon.fr   */
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
