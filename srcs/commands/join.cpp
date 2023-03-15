/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:37:27 by conobi            #+#    #+#             */
/*   Updated: 2023/03/15 04:02:45 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "Server.hpp"

void Command::join(Server &server, Client &client, const Input &input) {
	vector<string> channels;
	vector<string> keys;

	if (input.parameters().size() > 0 && !input.parameters()[0].empty())
		channels = Parser::parseCommas(input.parameters()[0]);
	if (input.parameters().size() > 1 && !input.parameters()[1].empty())
		keys = Parser::parseCommas(input.parameters()[1]);

	if (channels.size() == 0) {
		client.sendMessage(
			Output(server, &client, "461 JOIN", ":Not enough parameters"));
		return;
	}

	for (size_t i = 0; i < channels.size(); i++) {
		string channel_name = channels[i];
		string key = keys.size() > i ? keys[i] : "";

		if (!Parser::isChannelValid(channel_name)) {
			client.sendMessage(
				Output(server, &client, "403 " + channel_name,
					   ":Invalid channel name or no such channel exists"));
			continue;
		}

		vector<Channel>::iterator it = find(
			server.channels().begin(), server.channels().end(), channel_name);

		Channel *chan = &server.channels().back();

		// If channel doesn't exist, create it
		if ((server.channels().size() == 0 || it == server.channels().end()) &&
			channel_name[0] == '#') {
			Channel *new_chan = new Channel(channel_name, client, key);

			server.channels().push_back(*new_chan);
			chan = &server.channels().back();

			client.sendMessage(
				Output(server, &client, "JOIN " + channel_name, ""));

			continue;

		} else if (server.channels().size() > 0 &&
				   it == server.channels().end() && channel_name[0] != '#') {
			client.sendMessage(Output(server, &client, "403 " + channel_name,
									  ":No such channel"));
			continue;

		} else {
			chan = &*it;
		}

		if (chan->isBanned(client)) {
			client.sendMessage(Output(server, &client, "474 " + channel_name,
									  ":Cannot join channel (+b)"));
			continue;
		}

		if (chan->invite_mode() && !chan->isInvited(client)) {
			client.sendMessage(Output(server, &client, "473 " + channel_name,
									  ":Cannot join channel (+i)"));
			continue;
		}

		if (!chan->password_mode() && !key.empty() &&
			!chan->password().empty() && chan->password() != key) {
			client.sendMessage(Output(server, &client, "475 " + channel_name,
									  ":Cannot join channel (+k)"));
			continue;
		}

		chan->clientJoin(client);
		chan->broadcastMessage(
			Output(server, &client, "JOIN " + channel_name, ""), ROLE_NONE);
	}
}
