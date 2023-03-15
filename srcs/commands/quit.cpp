/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:16:25 by abastos           #+#    #+#             */
/*   Updated: 2023/03/15 18:17:26 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::quit(Server &server, Client &client, const Input &input) {
  string message = "Quit: ";

  if (input.parameters().size() == 1) {
    message.append(input.parameters()[0]);
  }

  // todo: maybe change this for loop
  for (vector<Channel>::iterator it = server.channels().begin();
		 it != server.channels().end(); it++) {
		if (it->clients().find(client) != it->clients().end()) {
      it->clientLeave(client);
      it->broadcastMessage(Output(server, &client, "QUIT", message), ROLE_NONE);
    }
	}

  client.sendMessage(Output(server, &client, "QUIT", message));

  server.closeClient(client);
}
