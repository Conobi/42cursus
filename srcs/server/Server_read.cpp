/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_read.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 02:53:50 by conobi            #+#    #+#             */
/*   Updated: 2023/02/24 02:57:42 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::_handleClientRead(Client &client) {
	string client_input = client.readInput();

	if (!client_input.empty())
		_logger.log("Client " + client.ip() + ":" +
						Utils::valToString(client.port()) + " said: \"" +
						client_input + "\"",
					false);
	else
		this->_closeClient(client);
}
