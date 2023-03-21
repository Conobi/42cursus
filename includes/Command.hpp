/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:00:34 by conobi            #+#    #+#             */
/*   Updated: 2023/03/21 17:27:11 by conobi           ###   ########lyon.fr   */
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
	private:
		static void registerUser(Server &server, Client &client);

	public:
		static void nick(Server &server, Client &client, const Input &input);
		static void ping(Server &server, Client &client, const Input &input);
		static void user(Server &server, Client &client, const Input &input);
		static void pass(Server &server, Client &client, const Input &input);
		static void quit(Server &server, Client &client, const Input &input);
		static void join(Server &server, Client &client, const Input &input);
		static void part(Server &server, Client &client, const Input &input);
		static void privmsg(Server &server, Client &client, const Input &input);
		static void mode(Server &server, Client &client, const Input &input);
		static void kick(Server &server, Client &client, const Input &input);
		static void names(Server &server, Client &client, const Input &input);
		static void invite(Server &server, Client &client, const Input &input);
		static void cap(Server &server, Client &client, const Input &input);
};
