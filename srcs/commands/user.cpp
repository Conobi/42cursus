/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:57:59 by abastos           #+#    #+#             */
/*   Updated: 2023/03/11 17:00:51 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "rpl.hpp"

/**
 * USER <username> 0 * <realname>
 * Reply:
 *  - ERR_NEEDMOREPARAMS (461)
 *  - ERR_ALREADYREGISTERED (462)
 * after this command if the client is registered this sends a welcome message
 */

static void registerUser(Server &server, Client &client) {
	client.sendMessage(Output(server, &client, "001 " + client.nick(), ":Welcome to the Internet Relay Network " + client.nick()));
}

void Command::user(Server &server, Client &client, const Input &input) {
	// todo: check if the client is already registered
	if (input.parameters().size() < 4) {
		client.sendMessage(Error::needmoreparams(input.command()));
		return;
	}

	if (client.authStatus() == REGISTERED) {
		client.sendMessage(Error::alreadyregistered());
		return;
	}

	client.username() = input.parameters()[0];
	if (client.authStatus() == AUTHENTICATED) {
		registerUser(server, client);
	}
}
