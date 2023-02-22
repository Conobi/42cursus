/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:26:11 by conobi            #+#    #+#             */
/*   Updated: 2023/02/22 01:40:33 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int fd, string ip, unsigned int port)
	: _fd(fd), _ip(ip), _port(port) {
	// Todo: check if the initialization values are correct (maybe)
	cout << FBLU("Client initialization constructor called.") << endl;
}

Client::~Client() {
	close(_fd);
	cout << FYEL("Client destructor called.") << endl;
}
