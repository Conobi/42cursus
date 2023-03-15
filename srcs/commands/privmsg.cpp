/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:23:02 by conobi            #+#    #+#             */
/*   Updated: 2023/03/15 17:18:02 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Command.hpp"

static void messageTarget(Server &server, Client &client, const string &target,
						  const string &message) {
	if (Parser::isChannelValid(target)) {
		Channel *chan = server.getChannel(target);
		if (chan == NULL) {
			client.sendMessage(Output(server, &client, "403", &client,
									  target + " :No such channel"));
			return;
		}
		if (!chan->external_message_mode() && !chan->isConnected(client)) {
			client.sendMessage(Output(server, &client, "442", &client,
									  target + " :You're not on that channel"));
			return;
		}
		chan->broadcastMessage(
			&client,
			Output(server, &client, "PRIVMSG", target + " :" + message),
			ROLE_NONE);
	} else if (Parser::isNickValid(target)) {
		Client *target_client = server.getClient(target);
		if (target_client == NULL) {
			client.sendMessage(Output(server, &client, "401", &client,
									  target + " :No such nick"));
			return;
		}
		target_client->sendMessage(
			Output(server, &client, "PRIVMSG", target + " :" + message));
	} else {
		client.sendMessage(Output(server, &client, "401", &client,
								  target + " :No such nick/channel"));
	}
}

void Command::privmsg(Server &server, Client &client, const Input &input) {
	vector<string> targets;
	string message;

	if (input.parameters().size() < 2) {
		client.sendMessage(Output(server, &client, "461 PRIVMSG", &client,
								  ":Not enough parameters"));
		return;
	}

	targets = Parser::parseCommas(input.parameters()[0]);
	message = input.parameters()[1];

	for (size_t i = 0; i < targets.size(); i++) {
		messageTarget(server, client, targets[i], message);
	}
}
