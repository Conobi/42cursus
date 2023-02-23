/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:26:28 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 02:28:10 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>

#include "Logger.hpp"
#include "Server.hpp"
#include "irc.hpp"

class Logger;

class Client {
	private:
		Client();

		int _fd;
		string _ip;
		unsigned int _port;

		Logger &_logger;

	public:
		Client(int fd, string ip, unsigned int port);
		~Client();
};
