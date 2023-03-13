/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:49:43 by abastos           #+#    #+#             */
/*   Updated: 2023/03/11 16:00:37 by abastos          ###   ########lyon.fr   */
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
		client.sendMessage(Error::nonicknamegiven());
		return;
	}

	string nick = input.parameters()[0];

	if (!Parser::isNickValid(nick)) {
		client.sendMessage(Error::oneusnickname(nick));
		return;
	}

	// if (client == nick) {
	// 	client.sendMessage(Error::nicknameinuse(nick));
	// 	if (client.authStatus() != REGISTERED)
	// 		client.authStatus() = ERRORED;
	// 	return;
	// }

	for (size_t i = 0; i < server.clients().size(); i++) {
		cout << "nick: " << server.clients()[i].nick() << endl;
		if (server.clients()[i] == nick) {
			client.sendMessage(Error::nicknameinuse(nick));
			return;
		}
	}

	client.nick() = nick;
}
