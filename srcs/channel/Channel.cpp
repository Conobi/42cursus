/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 00:35:41 by conobi            #+#    #+#             */
/*   Updated: 2023/03/13 14:45:04 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

#include <algorithm>
#include <stdexcept>
#include <vector>

Channel::Channel(const string &name, Client &op, const string &key)
	: _password(key),
	  _max_slots(0),
	  _invite_mode(false),
	  _password_mode(!key.empty()),
	  _ban_list_mode(false),
	  _slot_mode(false),
	  _secret_mode(false),
	  _protected_topic(false),
	  _external_message_mode(true),
	  _logger("Channel") {
	if (!isValidChannelName(name)) {
		throw runtime_error(
			"Invalid channel name given to Channel constructor.");
	}
	_name = name;
	clientJoin(op);
}

Channel::~Channel() {
}

void Channel::clientJoin(const Client &client) {
	if (this->_clients.find(client) != this->_clients.end()) {
		throw runtime_error("Client " + client.nick() + " already in channel " +
							this->_name);
		return;
	}
	this->_clients[client] = ROLE_NONE;
}

void Channel::clientLeave(const Client &client) {
	if (this->_clients.find(client) == this->_clients.end()) {
		throw runtime_error("Client " + client.nick() + " not in channel " +
							this->_name);
		return;
	}
	this->_clients.erase(client);
}

const ChannelRole &Channel::getRole(const Client &client) const {
	if (this->_clients.find(client) == this->_clients.end()) {
		throw runtime_error("Client " + client.nick() + " not in channel " +
							this->_name);
	}
	return this->_clients.at(client);
}

void Channel::setRole(const Client &client, const ChannelRole &role) {
	if (this->_clients.find(client) == this->_clients.end()) {
		throw runtime_error("Client " + client.nick() + " not in channel " +
							this->_name);
	}
	this->_clients[client] = role;
}

void Channel::inviteClient(const Client &client) {
	vector<Client> &list = this->_invite_list;

	if (this->isInvited(client)) {
		throw runtime_error("Client " + client.nick() +
							" already invited to channel " + this->_name);
	}
	list.push_back(client);
}

void Channel::uninviteClient(const Client &client) {
	vector<Client> &list = this->_invite_list;
	vector<Client>::iterator it;

	it = find(list.begin(), list.end(), client);
	if (it == list.end()) {
		throw runtime_error("Client " + client.nick() +
							" not invited to channel " + this->_name);
	}
	list.erase(it);
}

void Channel::banClient(const Client &client) {
	vector<Client> &list = this->_ban_list;

	if (this->isBanned(client)) {
		throw runtime_error("Client " + client.nick() +
							" already banned from channel " + this->_name);
	}
	list.push_back(client);
}

void Channel::unbanClient(const Client &client) {
	vector<Client> &list = this->_ban_list;
	vector<Client>::iterator it;

	it = find(list.begin(), list.end(), client);
	if (it == list.end()) {
		throw runtime_error("Client " + client.nick() +
							" not banned from channel " + this->_name);
	}
	list.erase(it);
}

void Channel::broadcastMessage(const string &message, const ChannelRole &role) {
	// C++98 style for loop
	for (map<Client, ChannelRole>::iterator it = this->_clients.begin();
		 it != this->_clients.end(); it++) {
		if (it->second >= role) {
			it->first.sendMessage(message);
		}
	}
}

bool Channel::isInvited(const Client &client) const {
	vector<Client> list = this->_invite_list;

	if (find(list.begin(), list.end(), client) != list.end())
		return true;
	return false;
}

bool Channel::isBanned(const Client &client) const {
	vector<Client> list = this->_ban_list;

	if (find(list.begin(), list.end(), client) != list.end())
		return true;
	return false;
}

bool Channel::isConnected(const Client &client) const {
	if (this->_clients.find(client) != this->_clients.end())
		return true;
	return false;
}

bool Channel::isOp(const Client &client) const {
	return this->getRole(client) == ROLE_OP;
}

bool Channel::isValidChannelName(const string &channel_name) {
	if (channel_name.empty() || channel_name[0] != '#')
		return false;
	for (size_t i = 1; i < channel_name.size(); i++) {
		if (channel_name[i] == ' ' || channel_name[i] == '\a' ||
			channel_name[i] == '\x7' || channel_name[i] == ',')
			return false;
	}
	return true;
}

bool Channel::operator==(const string &name) const {
	return (this->_name == name ? true : false);
}

bool Channel::operator==(const Channel &channel) const {
	return (this->_name == channel._name ? true : false);
}
