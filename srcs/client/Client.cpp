/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:26:11 by conobi            #+#    #+#             */
/*   Updated: 2023/03/09 01:01:36 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::~Client() {
	if (close(this->fd()) < -1) {
		throw runtime_error("Cannot close client fd. close(): " +
							Utils::valToString(strerror(errno)));
	}
	delete &this->_logger;
}

Client::Client(const Client &val) : _logger(*(new Logger(val._logger))) {
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
	: _fd(fd), _ip(ip), _port(port), _logger(*(new Logger("Client"))) {
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

string Client::nick() const {
	return this->_nick;
}

string Client::username() const {
	return this->_username;
}

void Client::setNick(const string &nick) {
	this->_nick = nick;
}

void Client::setUsername(const string &username) {
	this->_username = username;
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
