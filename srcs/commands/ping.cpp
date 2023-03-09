/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:49:15 by abastos           #+#    #+#             */
/*   Updated: 2023/03/09 13:28:11 by abastos          ###   ########lyon.fr   */
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
	// todo: parse arg an send a pong message to the client with the correct
	// token
	(void)server;
	string message("PONG " + input.parameters()[0] + "\r\n");
	client.sendMessage(message);
}
