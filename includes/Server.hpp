/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:52 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 01:20:52 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

#include <ctime>

#include "Socket.hpp"
#include "irc.hpp"

class Socket;

class Server {
	private:
		Server();

		Socket &_socket;

		bool _stop;
		ushort _port;
		string _password;

		int _guard(int code, const char *process);
		void _eventLoop();
		void _acceptNewClient();
		void _handleClientEvent(int client_fd, uint32_t revents);

	public:
		Server(const int port, const string password);
		~Server();

		static void log(const string &msg, const bool &verbose_only);
};
