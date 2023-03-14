/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:26:28 by conobi            #+#    #+#             */
/*   Updated: 2023/03/14 15:55:46 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <unistd.h>

#include "Channel.hpp"
#include "Logger.hpp"
#include "Server.hpp"
#include "irc.hpp"
#include "Output.hpp"

enum status { UNAUTHENTICATED, AUTHENTICATED, REGISTERED, ERRORED };

class Channel;
class Logger;

class Client {
	private:
		Client();

		int _fd;
		string _ip;
		ushort _port;
		string _nick;
		string _username;
		status _authStatus;

		Logger &_logger;

	public:
		~Client();
		Client(const Client &val);
		Client &operator=(const Client &rhs);

		Client(int fd, string ip, unsigned int port);

		int fd() const;
		string ip() const;
		ushort port() const;

		string &nick();
		const string &nick() const;
		string &username();
		const string &username() const;
		status &authStatus();
		const enum status &authStatus() const;

		string readInput();
		void sendMessage(const string &message) const;
		void sendMessage(const string &message, const string &target) const;

		void registerUser(Server &server);

		bool operator==(const int &fd) const;
		bool operator==(const Client &client) const;
		bool operator==(const string &nick) const;
		bool operator<(const Client &rhs) const;
};
