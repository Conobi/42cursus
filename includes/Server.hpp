/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:52 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 17:14:37 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <netinet/in.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <ctime>
#include <vector>

#include "Client.hpp"
#include "Logger.hpp"
#include "Socket.hpp"
#include "Utils.hpp"
#include "irc.hpp"

class Logger;
class Socket;
class Client;

class Server {
	private:
		Server();

		Logger &_logger;

		Socket &_socket;
		std::vector<Client> _clients;

		bool _stop;
		ushort _port;
		string _password;

		int _guard(int code, const char *process);
		void _eventLoop();

		void _epollHandler();
		void _epollFdHandler(const int ready_fds, struct epoll_event events[]);

		Client &_createNewClient();
		Client &_findClient(int client_fd);
		void _acceptNewClient();
		void _handleClientEvent(int client_fd, uint32_t revents);

	public:
		Server(const ushort port, const string password);
		~Server();
};
