/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:57:59 by abastos           #+#    #+#             */
/*   Updated: 2023/03/03 16:04:04 by abastos          ###   ########lyon.fr   */
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

void userCommand(Client &client, const string &arg) {
  (void)arg;
  // todo: check if the client is already registered
  client.setUsername("test");
  client.sendMessage(rpl::welcome("irc.com", client.nick()));
}
