/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:26:28 by conobi            #+#    #+#             */
/*   Updated: 2023/02/24 01:30:02 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>

#include "Logger.hpp"
#include "Server.hpp"
#include "irc.hpp"

class Logger;

class Client {
	private:
		Client();

		int _fd;
		string _ip;
		ushort _port;

		Logger &_logger;

	public:
		~Client();
		Client(const Client &val);
		Client &operator=(const Client &rhs);

		Client(int fd, string ip, unsigned int port);

		bool operator==(const int &fd) const {
			return this->fd() == fd;
		}

		int fd() const;
		string ip() const;
		ushort port() const;

		string readInput();
};
