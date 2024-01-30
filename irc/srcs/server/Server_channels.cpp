/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_channels.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 03:28:34 by conobi            #+#    #+#             */
/*   Updated: 2023/03/20 14:54:48 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Channel *Server::getChannel(const string &channel_name) {
	if (channel_name.empty())
		return NULL;
	vector<Channel>::iterator it =
		find(this->_channels.begin(), this->_channels.end(), channel_name);
	if (it != this->_channels.end())
		return &*it;
	return NULL;
}
