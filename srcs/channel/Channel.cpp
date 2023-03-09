/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 00:35:41 by conobi            #+#    #+#             */
/*   Updated: 2023/03/09 02:42:30 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(const string &name, Client &op, const string &key)
	: _password(key),
	  _max_slots(0),
	  _invite_list_mode(false),
	  _password_mode(!key.empty()),
	  _ban_list_mode(false),
	  _slot_mode(false),
	  _secret_mode(false),
	  _protected_topic(false),
	  _external_message_mode(true),
	  _logger(*(new Logger("Channel"))) {
	// todo: check the channel name, add user to the channel and set its role to
	// OP (1).
}

Channel::~Channel() {
	delete &this->_logger;
}
