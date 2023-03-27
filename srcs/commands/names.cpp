/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 00:12:05 by conobi            #+#    #+#             */
/*   Updated: 2023/03/27 18:18:48 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <vector>

#include "Channel.hpp"
#include "Command.hpp"

static void sendAllNames(Server &server, Client &client, Channel *channel) {
	for (map<Client, ChannelRole>::iterator member = channel->clients().begin();
		 member != channel->clients().end(); member++) {
		if (member->second == ROLE_OP)
			client.sendMessage(
				Output(server, &client, "353", &client,
					   "= " + channel->name() + " :@" + member->first.nick()));
		else
			client.sendMessage(
				Output(server, &client, "353", &client,
					   "= " + channel->name() + " :" + member->first.nick()));
	}
}

void Command::names(Server &server, Client &client, const Input &input) {
	if (client.authStatus() != REGISTERED) {
		client.sendMessage(Output(server, &client, "451", &client,
								  ":You have not registered"));
		return;
	}

	if (!input.parameters().size()) {
		for (vector<Channel>::iterator it = server.channels().begin();
			 it != server.channels().end(); it++) {
			sendAllNames(server, client, &*it);
		}
		client.sendMessage(
			Output(server, &client, "366", &client, ":End of /NAMES list"));
	} else {
		Channel *channel = server.getChannel(input.parameters()[0]);

		if (channel)
			sendAllNames(server, client, channel);
		client.sendMessage(
			Output(server, &client, "366", &client,
				   input.parameters()[0] + " :End of /NAMES list"));
	}
}
