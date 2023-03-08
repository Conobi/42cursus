/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:50:47 by abastos           #+#    #+#             */
/*   Updated: 2023/03/08 18:45:06 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "errors.hpp"

/**
 * PASS <password>
 * Reply:
 *  - ERR_NEEDMOREPARAMS (461)
 *  - ERR_ALREADYREGISTERED (462)
 *  - ERR_PASSWDMISMATCH (464)
 */

void Command::pass(Server &server, Client &client, const Input &input) {
	if (server.password() != input.parameters()[0]) {
		client.sendMessage(error::passwdmismatch(input.parameters()[0]));
		client.sendMessage("ERROR :Wrong password\r\n");
	}
}
