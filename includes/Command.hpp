/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:00:34 by conobi            #+#    #+#             */
/*   Updated: 2023/03/11 16:41:32 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "Server.hpp"
#include "errors.hpp"
#include "irc.hpp"

class Server;
class Client;

class Command {
	public:
		static void nick(Server &server, Client &client, const Input &input);
		static void ping(Server &server, Client &client, const Input &input);
		static void pong(Server &server, Client &client, const Input &input);
		static void user(Server &server, Client &client, const Input &input);
		static void pass(Server &server, Client &client, const Input &input);
		static void quit(Server &server, Client &client, const Input &input);
};
