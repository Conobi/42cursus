/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 00:35:41 by conobi            #+#    #+#             */
/*   Updated: 2023/03/27 14:58:19 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

#include <cctype>

Channel::Channel(const string &name, Client &op, const string &key)
	: _name(name),
	  _password(key),
	  _invite_mode(false),
	  _password_mode(!key.empty()),
	  _ban_list_mode(false),
	  _slot_mode(false),
	  _secret_mode(false),
	  _protected_topic(false),
	  _external_message_mode(false),
	  _logger("Channel") {
	if (!Parser::isChannelValid(name)) {
		throw runtime_error(
			"Invalid channel name given to Channel constructor.");
	}
	clientJoin(op);
	this->_clients[op] = ROLE_OP;
}

Channel::Channel(const Channel &rhs) : _logger(rhs._logger) {
	*this = rhs;
}

Channel &Channel::operator=(const Channel &rhs) {
	if (this != &rhs) {
		this->_name = rhs._name;
		this->_clients = rhs._clients;
		this->_invite_list = rhs._invite_list;
		this->_password = rhs._password;
		this->_ban_list = rhs._ban_list;
		this->_max_slots = rhs._max_slots;
		this->_topic = rhs._topic;
		this->_invite_mode = rhs._invite_mode;
		this->_password_mode = rhs._password_mode;
		this->_ban_list_mode = rhs._ban_list_mode;
		this->_slot_mode = rhs._slot_mode;
		this->_secret_mode = rhs._secret_mode;
		this->_protected_topic = rhs._protected_topic;
		this->_external_message_mode = rhs._external_message_mode;
	}
	return *this;
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

	// Remove client from invite list if he was invited
	vector<Client>::iterator it =
		find(this->_invite_list.begin(), this->_invite_list.end(), client);
	if (it != this->_invite_list.end()) {
		this->_invite_list.erase(it);
	}
}

void Channel::clientLeave(const Client &client) {
	map<Client, ChannelRole>::iterator it = this->_clients.find(client);
	if (it == this->_clients.end()) {
		throw runtime_error("Client " + client.nick() + " not in channel " +
							this->_name);
		return;
	}
	this->_clients.erase(it);
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

void Channel::broadcastMessage(const Client *sender, const string &message,
							   const ChannelRole &role) {
	// C++98 style for loop
	for (map<Client, ChannelRole>::iterator it = this->_clients.begin();
		 it != this->_clients.end(); it++) {
		if ((!sender || !(it->first == *sender)) && it->second >= role) {
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

bool Channel::operator==(const string &name) const {
	return (Utils::toLower(this->_name) == Utils::toLower(name) ? true : false);
}

bool Channel::operator==(const Channel &channel) const {
	return (Utils::toLower(this->_name) == Utils::toLower(channel._name)
				? true
				: false);
}
