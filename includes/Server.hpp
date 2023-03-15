/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:52 by conobi            #+#    #+#             */
/*   Updated: 2023/03/15 03:31:24 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fcntl.h>
#include <netinet/in.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

#include "Channel.hpp"
#include "Client.hpp"
#include "Input.hpp"
#include "Logger.hpp"
#include "Socket.hpp"
#include "Utils.hpp"
#include "irc.hpp"

class Logger;
class Socket;
class Client;
class Command;
class Input;
class Channel;

class Server {
	private:
		Server();

		Logger &_logger;

		Socket &_socket;
		vector<Client> _clients;
		vector<Channel> _channels;

		map<string, void (*)(Server &, Client &, const Input &)> _commands;

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

		void _handleClientRead(Client &client);

	public:
		Server(const ushort port, const string password);
		~Server();

		const string ip() const;

		const string &password() const { return _password; }
		string &password() { return _password; }

		const vector<Client> &clients() const { return _clients; }

		const vector<Channel> &channels() const { return _channels; }
		vector<Channel> &channels() { return _channels; }

		Channel *getChannel(const string &channel_name);

		void closeClient(const Client &client);
};
