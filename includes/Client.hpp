/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 23:26:28 by conobi            #+#    #+#             */
/*   Updated: 2023/02/22 18:43:41 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>

#include "Server.hpp"
#include "irc.hpp"

class Client {
	private:
		Client();

		int _fd;
		string _ip;
		unsigned int _port;

	public:
		Client(int fd, string ip, unsigned int port);
		~Client();
};
