/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_read.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 02:53:50 by conobi            #+#    #+#             */
/*   Updated: 2023/03/21 17:06:45 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::_handleClientRead(Client &client) {
	string client_input = client.readInput();

	if (client_input.empty()) {
		this->closeClient(client);
		return;
	}

	// Cut each individual command by \r\n
	while (client_input.find("\r\n") != string::npos) {
		string command = client_input.substr(0, client_input.find("\r\n"));
		client_input = client_input.substr(client_input.find("\r\n") + 2);

		Input input(command);

		if (!command.empty()) {
			_logger.log("Client " + client.ip() + ":" +
							Utils::valToString(client.port()) + " said: \"" +
							command + "\"",
						false);
			if (this->_commands[input.command()]) {
				this->_commands[input.command()](*this, client, input);
			} else {
				client.sendMessage(
					Output(*this, &client, "421", &client,
						   input.command() + " :Unknown command"));
				_logger.warn("Unknown command \"" + input.command() + "\"",
							 false);
			}
		} else
			this->closeClient(client);
	}
}
