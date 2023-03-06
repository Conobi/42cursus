/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:57:59 by abastos           #+#    #+#             */
/*   Updated: 2023/03/06 16:27:09 by conobi           ###   ########lyon.fr   */
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
	client.setUsername("test");
	client.sendMessage(rpl::welcome("irc.com", client.nick()));
}
