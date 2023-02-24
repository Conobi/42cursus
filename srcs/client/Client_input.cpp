/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_input.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 01:09:42 by conobi            #+#    #+#             */
/*   Updated: 2023/02/24 01:45:21 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>

#include "Client.hpp"
#include "Utils.hpp"

string Client::readInput() {
	const unsigned int MAX_BUF_LENGTH = 1024;
	std::vector<char> buffer(MAX_BUF_LENGTH);
	std::string input = "";
	ssize_t bytes_received = 0;

	// Append the read buffer to the string
	do {
		bytes_received = recv(this->fd(), &buffer[0], buffer.size(), 0);

		if (bytes_received == -1) {
			_logger.warn("Wasn't able to read the input from client " +
							 this->ip() + ":" +
							 Utils::valToString(this->port()) +
							 ". Reason: " + Utils::valToString(strerror(errno)),
						 false);
		}

		if (bytes_received > 0)
			input.append(buffer.begin(), buffer.end());
	} while (bytes_received == MAX_BUF_LENGTH);

	return (input);
}
