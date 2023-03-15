/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:00:34 by conobi            #+#    #+#             */
/*   Updated: 2023/03/14 20:16:17 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Channel.hpp"
#include "Client.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "Server.hpp"
#include "irc.hpp"

class Server;
class Client;
class Channel;

class Command {
	public:
		static void nick(Server &server, Client &client, const Input &input);
		static void ping(Server &server, Client &client, const Input &input);
		static void user(Server &server, Client &client, const Input &input);
		static void pass(Server &server, Client &client, const Input &input);
		static void quit(Server &server, Client &client, const Input &input);
		static void join(Server &server, Client &client, const Input &input);
};
