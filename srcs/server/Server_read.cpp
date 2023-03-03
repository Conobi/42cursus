/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_read.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 02:53:50 by conobi            #+#    #+#             */
/*   Updated: 2023/03/03 16:04:28 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::_handleClientRead(Client &client) {
	string client_input = client.readInput();

	if (!client_input.empty()) {
		_logger.log("Client " + client.ip() + ":" +
						Utils::valToString(client.port()) + " said: \"" +
						client_input + "\"",
					false);

		// for testing purposes
		if (client_input.find("NICK") != string::npos) {
			this->_commandManager.executeCommand(client, "NICK", "arg");
			return;
		}
		if (client_input.find("USER") != string::npos) {
			this->_commandManager.executeCommand(client, "USER", "arg");
			return;
		}
		if (client_input.find("PING") != string::npos) {
			this->_commandManager.executeCommand(client, "PING", "arg");
			return;
		}
	}
	else
		this->_closeClient(client);
}
