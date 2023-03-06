/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:49:43 by abastos           #+#    #+#             */
/*   Updated: 2023/03/06 16:28:14 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

/**
 * NICK <nickname>
 * Reply:
 *  - ERR_NONICKNAMEGIVEN (431)
 *  - ERR_ERRONEUSNICKNAME (432)
 *  - ERR_NICKNAMEINUSE (433)
 *  - ERR_NICKCOLLISION (436)
 *
 */
void Command::nick(Server &server, Client &client, const Input &input) {
	// todo: check if the nickname is valid
	client.setNick("test");
}
