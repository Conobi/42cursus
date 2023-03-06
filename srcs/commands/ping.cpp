/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:49:15 by abastos           #+#    #+#             */
/*   Updated: 2023/03/06 16:28:46 by conobi           ###   ########lyon.fr   */
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
	client.sendMessage("PONG localhost\r\n");
}
