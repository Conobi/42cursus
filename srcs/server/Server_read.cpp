/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_read.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 02:53:50 by conobi            #+#    #+#             */
/*   Updated: 2023/03/07 18:58:51 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::_handleClientRead(Client &client) {
	string client_input = client.readInput();
	Input input(client_input);

	if (!client_input.empty()) {
		_logger.log("Client " + client.ip() + ":" +
						Utils::valToString(client.port()) + " said: \"" +
						client_input + "\"",
					false);
		if (this->_commands[input.command()]) {
			this->_commands[input.command()](*this, client, input);
		} else {
			_logger.warn("Unknown command \"" + input.command() + "\"",
						 false);
			// todo: send an rpl_unknowncommand message
		}
	} else
		this->_closeClient(client);
}
