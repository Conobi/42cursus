/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:26:28 by conobi            #+#    #+#             */
/*   Updated: 2023/03/10 15:16:17 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <unistd.h>

#include "Logger.hpp"
#include "Server.hpp"
#include "irc.hpp"

enum status { UNREGISTERED, AUTHENTICATED, REGISTERED };

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
		void sendMessage(const string message) const;
		void sendMessage(const string message, const string &target) const;

		bool operator==(const int &fd) const;
		bool operator==(const Client &client) const;
		bool operator==(const string &nick) const;
		bool operator<(const Client &rhs) const;
};
