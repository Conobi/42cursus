/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:26:28 by conobi            #+#    #+#             */
/*   Updated: 2023/03/09 13:49:59 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <unistd.h>

#include "Logger.hpp"
#include "Server.hpp"
#include "irc.hpp"

enum authStatus { UNREGISTERED, AUTHENTICATED, REGISTERED };

class Logger;

class Client {
	private:
		Client();

		int _fd;
		string _ip;
		ushort _port;
		string _nick;
		string _username;
		authStatus _authStatus;

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
		authStatus &authStatus();
		const enum authStatus &authStatus() const;

		string readInput();
		void sendMessage(const string message) const;
		void sendMessage(const string message, const string &target) const;

		bool operator==(const int &fd) const;
		bool operator==(const Client &client) const;
		bool operator==(const string &nick) const;
};
