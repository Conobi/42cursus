/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:08:55 by conobi            #+#    #+#             */
/*   Updated: 2023/03/27 18:18:17 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Command.hpp"

void Command::invite(Server &server, Client &client, const Input &input) {
	if (client.authStatus() != REGISTERED) {
		client.sendMessage(Output(server, &client, "451", &client,
								  ":You have not registered"));
		return;
	}

	if (input.parameters().size() < 2) {
		client.sendMessage(Output(server, &client, "461", &client,
								  "INVITE :Not enough parameters"));
		return;
	}

	Client *target = server.getClient(input.parameters()[0]);
	Channel *chan = server.getChannel(input.parameters()[1]);

	if (!target) {
		client.sendMessage(
			Output(server, &client, "401", &client,
				   input.parameters()[0] + " :No such nick/channel"));
		return;
	}

	if (!chan) {
		client.sendMessage(
			Output(server, &client, "403", &client,
				   input.parameters()[1] +
					   " :Invalid channel name or no such channel exists"));
		return;
	}

	if (!chan->isConnected(client)) {
		client.sendMessage(
			Output(server, &client, "442", &client,
				   chan->name() + " :You're not on that channel"));
		return;
	}

	if (!chan->isOp(client)) {
		client.sendMessage(
			Output(server, &client, "482", &client,
				   chan->name() + " :You're not channel operator"));
		return;
	}

	if (chan->isConnected(*target)) {
		client.sendMessage(Output(
			server, &client, "443", &client,
			target->nick() + " " + chan->name() + " :is already on channel"));
		return;
	}

	if (chan->isInvited(*target)) {
		client.sendMessage(Output(server, &client, "443", &client,
								  target->nick() + " " + chan->name() +
									  " :is already invited to channel"));
		return;
	}

	chan->inviteClient(*target);
	target->sendMessage(
		Output(server, &client, "INVITE", target, ":" + chan->name()));
	client.sendMessage(Output(server, &client, "341", &client,
							  target->nick() + " :" + chan->name()));
}
