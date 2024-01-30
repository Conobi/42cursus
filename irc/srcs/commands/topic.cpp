/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:57:02 by abastos           #+#    #+#             */
/*   Updated: 2023/03/27 18:20:30 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::topic(Server &server, Client &client, const Input &input) {
	if (client.authStatus() != REGISTERED) {
		client.sendMessage(Output(server, &client, "451", &client,
								  ":You have not registered"));
		return;
	}

	if (input.parameters().size() < 1) {
		client.sendMessage(Output(server, NULL, "461",
								  input.command() + " :Not enough parameters"));
		return;
	}

	string target = input.parameters()[0];

	Channel *channel = server.getChannel(target);

	if (!channel) {
		client.sendMessage(Output(
			server, &client, "403",
			client.nick() + " " + channel->name() + " :No such channel"));
		return;
	}

	if (input.parameters().size() == 1) {
		if (channel->topic().empty()) {
			client.sendMessage(Output(
				server, &client, "331",
				client.nick() + " " + channel->name() + " :No topic set"));
			return;
		}
		client.sendMessage(Output(
			server, &client, "332",
			client.nick() + " " + channel->name() + " :" + channel->topic()));
		return;
	}

	if (!channel->isConnected(client)) {
		client.sendMessage(Output(server, &client, "442",
								  client.nick() + " " + channel->name() +
									  " :You're not on that channel"));
		return;
	}

	if (!channel->isOp(client)) {
		client.sendMessage(Output(server, &client, "482",
								  client.nick() + " " + channel->name() +
									  " :You're not channel operator"));
		return;
	}

	string topic = input.parameters()[1];

	if (input.parameters()[1].empty()) {
		topic = "";
	}

	channel->topic() = topic;

	channel->broadcastMessage(
		NULL,
		Output(server, &client, "332",
			   client.nick() + " " + target + " :" + topic),
		ROLE_NONE);
}
