/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:29:52 by conobi            #+#    #+#             */
/*   Updated: 2023/02/21 19:29:56 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fcntl.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "irc.hpp"

class Server {
	private:
		Server();

		bool _stop;
		int _port;
		int _tcp_fd;
		string _password;
		struct sockaddr_in _sock_addr;
		struct _sockaddr_in_serv_addr;
		struct _cli_addr;

		int _guard(int code, const char *process);
		void _eventHandler();
		void _eventLoop(int ep_fd);

	public:
		Server(const int port, const string password);
		~Server();

		int createSocket(const int domain, const int type, const int protocol);
		void setSocketAddr(const int port);
		void bindSocket(const int socket);
};
