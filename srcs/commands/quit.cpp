/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:16:25 by abastos           #+#    #+#             */
/*   Updated: 2023/03/21 20:54:12 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::quit(Server &server, Client &client, const Input &input) {
	string message = "Quit: ";

	if (input.parameters().size() == 1) {
		message.append(input.parameters()[0]);
	}

	for (vector<Channel>::iterator channel = server.channels().begin();
		 channel != server.channels().end(); channel++) {
		if (channel->clients().find(client) != channel->clients().end()) {
			channel->clientLeave(client);
			channel->broadcastMessage(
				NULL, Output(server, &client, "QUIT", ":" + message),
				ROLE_NONE);
			if (channel->clients().size() == 0) {
				vector<Channel>::iterator last_channel = channel;
				advance(last_channel, -1);
				server.channels().erase(find(server.channels().begin(),
											 server.channels().end(),
											 *channel));
				channel = last_channel;
			}
		}
	}

	client.sendMessage(
		Output(server, &client, "ERROR",
			   "Closing Link: " + client.ip() + " (Disconnected by client)"));

	server.closeClient(client);
}
