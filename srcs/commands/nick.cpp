/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:49:43 by abastos           #+#    #+#             */
/*   Updated: 2023/03/14 16:05:21 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

// todo: test auth flow with invalid nicknames

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
		client.sendMessage(Output(server, &client, "431", "No nickname given"));
		return;
	}

	string nick = input.parameters()[0];

	if (!Parser::isNickValid(nick)) {
		client.sendMessage(Output(server, &client, "432 " + nick, "Erroneous nickname"));
		return;
	}

	if (find(server.clients().begin(), server.clients().end(), nick) != server.clients().end()) {
		client.sendMessage(Output(server, &client, "433 " + nick, "Nickname is already in use"));
		return;
	}

	client.nick() = nick;
	if (!client.username().empty()) {
		client.registerUser(server);
	}
}
