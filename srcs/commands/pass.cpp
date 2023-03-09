/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:50:47 by abastos           #+#    #+#             */
/*   Updated: 2023/03/09 13:43:16 by abastos          ###   ########lyon.fr   */
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
	if (server.password() != input.parameters()[0]) {
		client.sendMessage(Error::passwdmismatch(input.parameters()[0]));
		client.sendMessage("Error :Authentication failed\r\n");
		return;
	}
	client.registered() = true;
}
