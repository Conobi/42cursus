/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:00:34 by conobi            #+#    #+#             */
/*   Updated: 2023/03/06 16:27:52 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "Input.hpp"
#include "Server.hpp"
#include "irc.hpp"

class Server;
class Client;

class Command {
	public:
		static void nick(Server &server, Client &client, const Input &input);
		static void ping(Server &server, Client &client, const Input &input);
		static void user(Server &server, Client &client, const Input &input);
};
