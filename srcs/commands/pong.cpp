/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:40:48 by abastos           #+#    #+#             */
/*   Updated: 2023/03/11 16:51:22 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void Command::pong(Server &server, Client &client, const Input &input) {
	if (input.parameters().size() < 1) {
		client.sendMessage(Error::needmoreparams(input.command()));
		return;
	}

	string origin = input.parameters()[0];

	if (origin.empty()) {
		// client.sendMessage(Error::noorigin());
		return;
	}
  (void)server;
}
