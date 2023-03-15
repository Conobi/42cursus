/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_send.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:37:16 by abastos           #+#    #+#             */
/*   Updated: 2023/03/14 20:13:34 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

void Client::sendMessage(const string &message) const {
	// Check if client is still connected
	if (fcntl(this->_fd, F_GETFD) != -1 || errno != EBADF) {
		// Send message to client
		if (send(this->_fd, message.c_str(), message.size(), 0) == -1) {
			this->_logger.err("Error while sending message to client " +
							  this->_ip + ":" +
							  Utils::valToString(this->_port));
			return;
		}

		this->_logger.log("Message sent to " + this->_ip + ":" +
							  Utils::valToString(this->_port) + " \"" +
							  message.substr(0, message.size() - 2) + "\"",
						  false);
		return;
	}
	this->_logger.err("Error while sending message to client " + this->_ip +
					  ":" + Utils::valToString(this->_port) +
					  ": Client disconnected");
}
