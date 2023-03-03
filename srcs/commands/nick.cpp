/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:49:43 by abastos           #+#    #+#             */
/*   Updated: 2023/03/03 16:01:22 by abastos          ###   ########lyon.fr   */
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

void nickCommand(Client &client, const string &arg) {
  (void)arg;
  // todo: check if the nickname is valid
  client.setNick("test");
}
