/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:50:47 by abastos           #+#    #+#             */
/*   Updated: 2023/03/09 19:20:19 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

/**
 * PASS <password>
 * Reply:
 *  - ERR_NEEDMOREPARAMS (461)
 *  - ERR_ALREADYREGISTERED (462)
 *  - ERR_PASSWDMISMATCH (464)
 */

void Command::pass(Server &server, Client &client, const Input &input) {
	if (input.parameters().size() < 1) {
		client.sendMessage(Error::needmoreparams(input.command()));
		return;
	}

	if (client.authStatus() == AUTHENTICATED) {
		client.sendMessage(Error::alreadyregistered());
		return;
	}

	if (server.password() != input.parameters()[0]) {
		client.sendMessage(Error::passwdmismatch(input.parameters()[0]));
		client.sendMessage("Error :Authentication failed\r\n");
		return;
	}
	client.authStatus() = AUTHENTICATED;
}
