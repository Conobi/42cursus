/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 00:03:10 by conobi            #+#    #+#             */
/*   Updated: 2023/02/22 19:31:50 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include "SystemException.hpp"
#include "irc.hpp"

class Socket {
	private:
		Socket();

		ushort _port;
		int _address;
		int _sock_fd;
		int _epoll_fd;
		int _type;
		int _protocol;
		struct sockaddr_in _sock_addr;
		struct _cli_addr;

	public:
		Socket(const int domain, const int type, const int protocol);
		~Socket() throw();

		void bindAddress(const in_addr_t addr, const uint port);
		void bindAddress(const uint port);
		int createEpollFd();
		void listenTo(int max_connections);

		int sock_fd();
		int epoll_fd();

		static void epollAdd(int epoll_fd, int fd, uint32_t events);
		static void epollDelete(int epoll_fd, int fd);

		class SocketCreationException : public SystemException {
			public:
				SocketCreationException(const string &msg);
		};

		class BindException : public SystemException {
			public:
				BindException(const string &msg);
		};

		class UndefinedFdException : public SystemException {
			public:
				UndefinedFdException(const string &msg);
		};

		class EpollCtlException : public SystemException {
			public:
				EpollCtlException(const string &msg);
		};
};
