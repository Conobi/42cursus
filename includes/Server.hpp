/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:52 by conobi            #+#    #+#             */
/*   Updated: 2023/03/02 17:59:55 by abastos          ###   ########lyon.fr   */
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
#include "CommandManager.hpp"
#include "Logger.hpp"
#include "Socket.hpp"
#include "Utils.hpp"
#include "irc.hpp"

class Logger;
class Socket;
class Client;
class CommandManager;

class Server {
	private:
		Server();

		Logger &_logger;

		Socket &_socket;
		vector<Client> _clients;

		CommandManager &_commandManager;

		bool _stop;
		ushort _port;
		string _password;

		void _epollHandler(const int timeout, struct epoll_event events[],
						   const int maxevents);
		void _epollFdHandler(const int ready_fds, struct epoll_event events[]);
		void _startServer();

		Client &_createNewClient();
		Client &_findClient(int client_fd);
		void _acceptNewClient();
		void _handleClientEvent(int client_fd, uint32_t revents);
		void _closeClient(const Client &client);

		void _handleClientRead(Client &client);

	public:
		Server(const ushort port, const string password);
		~Server();
};
