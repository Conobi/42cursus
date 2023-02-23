/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:52 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 04:14:12 by conobi           ###   ########lyon.fr   */
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

		void _epollHandler();
		void _epollFdHandler(const int ready_fds, struct epoll_event events[]);

		void _acceptNewClient(int client_fd);
		void _handleClientEvent(int client_fd, uint32_t revents);

	public:
		Server(const int port, const string password);
		~Server();
};
