/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_send.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:37:16 by abastos           #+#    #+#             */
/*   Updated: 2023/03/09 02:44:48 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

void Client::sendMessage(const string message) const {
	// Check if client is still connected
	if (fcntl(this->_fd, F_GETFD) != -1 || errno != EBADF) {
		// Send message to client
		// todo: c_str() not working because c++ concatenation is shit, like
		// this language
		if (send(this->_fd, message.c_str(), message.size(), 0) == -1) {
			this->_logger.err("Error while sending message to client " +
							  this->_ip + ":" +
							  Utils::valToString(this->_port));
			return;
		}

		// todo: move this to Utils (but this create an error, fuck c++)
		std::string result = message;
		result.erase(message.find_last_not_of("\r\n") + 1);

		this->_logger.log("Message sent to client " + this->_ip + ":" +
							  Utils::valToString(this->_port) + " \"" +
							  result.c_str() + "\"",
						  false);
		return;
	}
	this->_logger.err("Error while sending message to client " + this->_ip +
					  ":" + Utils::valToString(this->_port) +
					  ": Client disconnected");
}
