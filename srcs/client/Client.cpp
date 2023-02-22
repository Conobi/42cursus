/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:26:11 by conobi            #+#    #+#             */
/*   Updated: 2023/02/22 18:46:58 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

#include <cstring>
#include <sstream>

#include "SystemException.hpp"

Client::Client(int fd, string ip, unsigned int port)
	: _fd(fd), _ip(ip), _port(port) {
	// Todo: check if the initialization values are correct (maybe)
	Server::log(FBLU("Client initialization constructor called."), true);
}

Client::~Client() {
	if (close(_fd) < -1) {
		stringstream err_msg;
		err_msg << "Cannot close client fd. close(): " << strerror(errno);
		throw SystemException(err_msg.str());
	}
	Server::log(FBLU("Client destructor called."), true);
}
