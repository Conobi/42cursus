/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:57:59 by abastos           #+#    #+#             */
/*   Updated: 2023/03/21 17:37:44 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

/**
 * USER <username> 0 * <realname>
 * Reply:
 *  - ERR_NEEDMOREPARAMS (461)
 *  - ERR_ALREADYREGISTERED (462)
 * after this command if the client is registered this sends a welcome message
 */

void Command::user(Server &server, Client &client, const Input &input) {
	if (input.parameters().size() < 4) {
		client.sendMessage(Output(server, &client, "461",
								  input.command() + " :Not enough parameters"));
		return;
	}

	if (client.authStatus() == REGISTERED) {
		client.sendMessage(Output(server, &client, "462", &client,
								  "You are already registered"));
		return;
	}

	client.username() = input.parameters()[0];
	if (!client.nick().empty()) {
		registerUser(server, client);
	}
}
