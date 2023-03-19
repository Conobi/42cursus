/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 22:23:22 by conobi            #+#    #+#             */
/*   Updated: 2023/03/20 00:01:23 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <vector>

#include "Command.hpp"

void Command::kick(Server &server, Client &client, const Input &input) {
	if (input.parameters().size() < 2) {
		client.sendMessage(Output(server, &client, "461", &client,
								  input.command() + " :Not enough parameters"));
		return;
	}

	Channel *channel = server.getChannel(input.parameters()[0]);

	if (!channel) {
		client.sendMessage(
			Output(server, &client, "403", &client,
				   input.parameters()[0] +
					   " :Invalid channel name or no such channel exists"));
		return;
	}

	if (!channel->isConnected(client)) {
		client.sendMessage(
			Output(server, &client, "442", &client,
				   input.parameters()[0] + " :You're not on that channel"));
		return;
	}

	if (!channel->isOp(client)) {
		client.sendMessage(
			Output(server, &client, "482", &client,
				   input.parameters()[0] + " :You're not channel operator"));
		return;
	}

	vector<string> targets = Parser::parseCommas(input.parameters()[1]);

	for (vector<string>::iterator it = targets.begin(); it != targets.end();
		 it++) {
		Client *target = server.getClient(*it);

		if (!target) {
			client.sendMessage(Output(server, &client, "401", &client,
									  *it + " :No such nick"));
			continue;
		}

		if (!channel->isConnected(*target)) {
			client.sendMessage(Output(server, &client, "441", &client,
									  target->nick() + " " +
										  input.parameters()[0] +
										  " :They aren't on that channel"));
			continue;
		}

		if (input.parameters().size() > 2) {
			channel->broadcastMessage(NULL,
									  Output(server, &client, "KICK",
											 input.parameters()[0] + " " + *it +
												 " :" + input.parameters()[2]),
									  ROLE_NONE);
		} else
			channel->broadcastMessage(NULL,
									  Output(server, &client, "KICK",
											 input.parameters()[0] + " " + *it),
									  ROLE_NONE);

		channel->clientLeave(*target);
	}

	if (channel->clients().size() == 0) {
		server.channels().erase(
			find(server.channels().begin(), server.channels().end(), *channel));
	}
}
