/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_channels.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 03:28:34 by conobi            #+#    #+#             */
/*   Updated: 2023/03/15 03:31:18 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Channel *Server::getChannel(const string &channel_name) {
	for (vector<Channel>::iterator it = this->_channels.begin();
		 it != this->_channels.end(); it++) {
		if ((*it).name() == channel_name)
			return &*it;
	}
	return NULL;
}
