/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:26:28 by conobi            #+#    #+#             */
/*   Updated: 2023/03/08 14:02:11 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
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
		ushort _port;
		string _nick;
		string _username;

		Logger &_logger;

	public:
		~Client();
		Client(const Client &val);
		Client &operator=(const Client &rhs);

		Client(int fd, string ip, unsigned int port);

		bool operator==(const int &fd) const {
			return this->fd() == fd;
		}

		int fd() const;
		string ip() const;
		ushort port() const;
		string nick() const;
		string username() const;

		void setNick(const string &nick);
		void setUsername(const string &username);

		string readInput();
		void sendMessage(const string message) const;
		void sendMessage(const string message, const string &target) const;
};
