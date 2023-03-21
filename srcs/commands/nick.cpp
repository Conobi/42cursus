/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:49:43 by abastos           #+#    #+#             */
/*   Updated: 2023/03/21 17:37:35 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

/**
 * NICK <nickname>
 * Reply:
 *  - ERR_NONICKNAMEGIVEN (431)
 *  - ERR_ERRONEUSNICKNAME (432)
 *  - ERR_NICKNAMEINUSE (433)
 *  - ERR_NICKCOLLISION (436)
 *
 */
void Command::nick(Server &server, Client &client, const Input &input) {
	if (input.parameters().size() < 1) {
		client.sendMessage(
			Output(server, &client, "431", ":No nickname given"));
		return;
	}

	string nick = input.parameters()[0];

	if (!Parser::isNickValid(nick)) {
		client.sendMessage(
			Output(server, &client, "432", nick + " :Erroneous nickname"));
		return;
	}

	if (find(server.clients().begin(), server.clients().end(), nick) !=
		server.clients().end()) {
		client.sendMessage(Output(server, &client, "433",
								  nick + " :Nickname is already in use"));
		return;
	}

	if (client.authStatus() == REGISTERED) {
		for (vector<Client>::const_iterator it = server.clients().begin();
			 it != server.clients().end(); it++) {
			if (it->authStatus() == REGISTERED) {
				it->sendMessage(Output(server, &client, "NICK", nick));
			}
		}
	}

	client.nick() = nick;
	if (!client.username().empty() && client.authStatus() != REGISTERED) {
		registerUser(server, client);
	}
}
