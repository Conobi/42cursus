/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:52 by conobi            #+#    #+#             */
/*   Updated: 2023/03/21 17:39:14 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Channel.hpp"
#include "Client.hpp"
#include "Command.hpp"
#include "Input.hpp"
#include "Logger.hpp"
#include "Socket.hpp"
#include "Utils.hpp"
#include "irc.hpp"

const int MAX_USERS = 9999;
const int MAX_EVENTS = 32;

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
		string _creation_date;

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

		const string &creationDate() const { return _creation_date; }

		const string ip() const;

		const string &password() const { return _password; }
		string &password() { return _password; }

		const vector<Client> &clients() const { return _clients; }

		const vector<Channel> &channels() const { return _channels; }
		vector<Channel> &channels() { return _channels; }

		Channel *getChannel(const string &channel_name);
		Client *getClient(const string &client_nick);

		const Logger &logger() const { return _logger; }

		void closeClient(const Client &client);
};
