/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:52 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 02:27:55 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

#include <ctime>

#include "Logger.hpp"
#include "Socket.hpp"
#include "irc.hpp"

class Logger;
class Socket;

class Server {
	private:
		Server();

		Socket &_socket;

		bool _stop;
		ushort _port;
		string _password;

		Logger &_logger;

		int _guard(int code, const char *process);
		void _eventLoop();
		void _acceptNewClient();
		void _handleClientEvent(int client_fd, uint32_t revents);

	public:
		Server(const int port, const string password);
		~Server();
};
