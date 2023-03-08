/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_read.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 02:53:50 by conobi            #+#    #+#             */
/*   Updated: 2023/03/08 14:39:35 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
// #include "rpl.hpp"

void Server::_handleClientRead(Client &client) {
	string client_input = client.readInput();

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
				_logger.warn("Unknown command \"" + input.command() + "\"",
							false);
			}
		} else
			this->_closeClient(client);
	}


}
