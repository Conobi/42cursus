/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:16:25 by abastos           #+#    #+#             */
/*   Updated: 2023/03/11 17:03:42 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::quit(Server &server, Client &client, const Input &input) {
  string message = "Quit: ";

  if (input.parameters().size() > 1) {
    message.append(input.parameters()[1]);
  }

  // todo: send a quit message to all the channels the client is in

  client.sendMessage(Output(server, &client, "QUIT", message));

  server.closeClient(client);
}
