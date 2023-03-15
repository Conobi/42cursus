/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:49:15 by abastos           #+#    #+#             */
/*   Updated: 2023/03/15 14:13:09 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

/**
 * Reply:
 *  - ERR_NEEDMOREPARAMS (461)
 *  - ERR_NOORIGIN (409)
 * send a pong message to the client
 */

void Command::ping(Server &server, Client &client, const Input &input) {
	if (input.parameters().size() < 1) {
		client.sendMessage(Output(server, &client, "461", input.command() + " :Not enough parameters"));
		return;
	}

	string origin = input.parameters()[0];

	if (origin.empty()) {
		// client.sendMessage(Error::noorigin());
		return;
	}

	client.sendMessage(Output(server, &client, "PONG", origin));
}
