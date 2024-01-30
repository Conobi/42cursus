/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:50:47 by abastos           #+#    #+#             */
/*   Updated: 2023/03/27 18:19:09 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

/**
 * PASS <password>
 * Reply:
 *  - ERR_NEEDMOREPARAMS (461)
 *  - ERR_ALREADYREGISTERED (462)
 *  - ERR_PASSWDMISMATCH (464)
 */

void Command::pass(Server &server, Client &client, const Input &input) {
	if (input.parameters().size() < 1) {
		client.sendMessage(Output(server, &client, "461",
								  input.command() + " :Not enough parameters"));
		return;
	}

	if (client.authStatus() == AUTHENTICATED) {
		client.sendMessage(
			Output(server, &client, "462 ", " :You are already registered"));
		return;
	}

	if (server.password() != input.parameters()[0]) {
		client.sendMessage(
			Output(server, &client, "464",
				   input.parameters()[0] + " :Password incorrect"));
		client.sendMessage(
			Output(server, &client, "ERROR",
				   "Closing Link: " + client.ip() + " (Password incorrect)"));
		server.closeClient(client);
		return;
	}
	client.authStatus() = AUTHENTICATED;
}
