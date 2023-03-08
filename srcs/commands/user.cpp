/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:57:59 by abastos           #+#    #+#             */
/*   Updated: 2023/03/08 02:11:11 by abastos          ###   ########lyon.fr   */
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

void Command::user(Server &server, Client &client, const Input &input) {
	// todo: check if the client is already registered
	client.setUsername(input.parameters()[0]);
	(void)server;
	client.sendMessage(rpl::welcome("irc@example.com", client.nick()));
}
