/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:26:11 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 02:51:42 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

#include <cstring>
#include <sstream>
#include <stdexcept>

Client::Client(int fd, string ip, unsigned int port)
	: _fd(fd), _ip(ip), _port(port), _logger(*(new Logger("Client"))) {
	// Todo: check if the initialization values are correct (maybe)
}

Client::~Client() {
	if (close(_fd) < -1) {
		stringstream err_msg;
		err_msg << "Cannot close client fd. close(): " << strerror(errno);
		throw runtime_error(err_msg.str());
	}
	delete &this->_logger;
}
