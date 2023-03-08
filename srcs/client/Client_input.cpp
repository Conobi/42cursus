/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client_input.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 01:09:42 by conobi            #+#    #+#             */
/*   Updated: 2023/03/08 14:16:10 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

string Client::readInput() {
	const unsigned int MAX_BUF_LENGTH = 512;
	vector<char> buffer(MAX_BUF_LENGTH);
	string input = "";
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
			input.append(buffer.begin(), buffer.begin() + bytes_received);
	} while (bytes_received == MAX_BUF_LENGTH);

	return (input);
}
