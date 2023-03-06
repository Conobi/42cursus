/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_read.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 02:53:50 by conobi            #+#    #+#             */
/*   Updated: 2023/03/06 18:48:39 by conobi           ###   ########lyon.fr   */
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
		// todo: execute command based on input parsing
	} else
		this->_closeClient(client);
}
