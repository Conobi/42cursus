/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:49:15 by abastos           #+#    #+#             */
/*   Updated: 2023/03/03 16:01:31 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

/**
 * Reply:
 *  - ERR_NEEDMOREPARAMS (461)
 *  - ERR_NOORIGIN (409)
 * send a pong message to the client
 */

void pingCommand(Client &client, const string &arg) {
  (void)arg;
  // todo: parse arg an send a pong message to the client with the correct token
  client.sendMessage("PONG localhost\r\n");
}
