/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 03:25:25 by conobi            #+#    #+#             */
/*   Updated: 2023/03/15 18:36:16 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.hpp"
#include "Output.hpp"

void Command::part(Server &server, Client &client, const Input &input) {
	if (input.parameters().size() < 1) {
		client.sendMessage(Output(server, &client, "461", &client,
								  input.command() + " :Not enough parameters"));
		return;
	}

	vector<string> channels = Parser::parseCommas(input.parameters()[0]);

	for (vector<string>::iterator it = channels.begin(); it != channels.end();
		 it++) {
		if (!Parser::isChannelValid(*it)) {
			client.sendMessage(Output(
				server, &client, "403", &client,
				*it + " :Invalid channel name or no such channel exists"));
			continue;
		}

		Channel *channel = server.getChannel(*it);

		if (!channel) {
			client.sendMessage(Output(
				server, &client, "403", &client,
				*it + " :Invalid channel name or no such channel exists"));
			continue;
		}
		if (!channel->isConnected(client)) {
			client.sendMessage(Output(server, &client, "442", &client,
									  *it + " :You're not on that channel"));
			continue;
		}

		channel->clientLeave(client);
		client.sendMessage(Output(server, &client, "PART", ":" + *it));

		if (input.parameters().size() > 1) {
			channel->broadcastMessage(
				NULL,
				Output(server, &client, "PART",
					   *it + " :" + input.parameters()[1]),
				ROLE_NONE);
		} else
			channel->broadcastMessage(
				NULL, Output(server, &client, "PART", ":" + *it), ROLE_NONE);

		if (channel->clients().size() == 0) {
			server.channels().erase(
				find(server.channels().begin(), server.channels().end(), *it));
		}
	}
}
