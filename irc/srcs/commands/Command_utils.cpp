/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:24:11 by conobi            #+#    #+#             */
/*   Updated: 2023/03/21 17:42:20 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::registerUser(Server &server, Client &client) {
	if (client.authStatus() == REGISTERED) {
		server.logger().info("Client " + client.nick() + " tried to reregister",
							 false);
		client.sendMessage(
			Output(server, &client, "462", &client, ":You may not reregister"));
		return;
	}

	if (client.authStatus() == UNAUTHENTICATED) {
		server.logger().info(
			"Client " + client.nick() + " is not authenticated", false);
		client.sendMessage(Output(server, &client, "451", &client,
								  ":You have not registered"));
		return;
	}

	client.authStatus() = REGISTERED;
	client.sendMessage(
		Output(server, &client, "001", &client,
			   ":Welcome to our ft_irc server, " + client.nick() + "!"));
	client.sendMessage(Output(
		server, &client, "002", &client,
		":You are connected to " + server.ip() + ", running version 1.0"));
	client.sendMessage(
		Output(server, &client, "003", &client,
			   ":This server was created " + server.creationDate()));
	client.sendMessage(
		Output(server, &client, "004", &client, server.ip() + " 1.0 o :ik"));
	server.logger().info("Client " + client.nick() + " registered", false);
}
