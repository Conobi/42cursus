/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 00:35:54 by conobi            #+#    #+#             */
/*   Updated: 2023/03/13 14:44:57 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "Logger.hpp"
#include "Output.hpp"
#include "Utils.hpp"
#include "irc.hpp"

// Created on user join, deleted when the last user leaves.
// First char MUST be a #, and a channel name cannot contains any spaces,
// 0x07/CTRL^D/BELL or commas.
// The user creating the channel become the OP.
// A channel contains a TOPIC
// Warning: What to do when the OP leaves the channel?

enum ChannelRole {
	ROLE_NONE = 0,
	ROLE_OP = 1,
	ROLE_VOICE = 2,
	ROLE_HALFOP = 3,
	ROLE_USER = 4
};

class Client;

class Channel {
	private:
		Channel();

		string _name;
		map<Client, ChannelRole> _clients;

		vector<Client> _invite_list;
		string _password;
		vector<Client> _ban_list;
		uint _max_slots;
		string _topic;

		bool _invite_mode;
		bool _password_mode;
		bool _ban_list_mode;
		bool _slot_mode;
		bool _secret_mode;
		bool _protected_topic;
		bool _external_message_mode;

		Logger _logger;

	public:
		Channel(const string &name, Client &op, const string &key);
		~Channel();

		void clientJoin(const Client &client);
		void clientLeave(const Client &client);

		const ChannelRole &getRole(const Client &client) const;
		void setRole(const Client &client, const ChannelRole &role);

		void inviteClient(const Client &client);
		void uninviteClient(const Client &client);

		void banClient(const Client &client);
		void unbanClient(const Client &client);

		void broadcastMessage(const string &message, const ChannelRole &role);

		bool isInvited(const Client &client) const;
		bool isBanned(const Client &client) const;
		bool isConnected(const Client &client) const;
		bool isOp(const Client &client) const;

		static bool isValidChannelName(const string &channel_name);

		bool &invite_mode() { return _invite_mode; }
		const bool &invite_mode() const { return _invite_mode; }

		bool &ban_list_mode() { return _ban_list_mode; }
		const bool &ban_list_mode() const { return _ban_list_mode; }

		bool &password_mode() { return _password_mode; }
		const bool &password_mode() const { return _password_mode; }

		string &password() { return _password; }
		const string &password() const { return _password; }

		string &topic() { return _topic; }
		const string &topic() const { return _topic; }

		bool &protected_topic() { return _protected_topic; }
		const bool &protected_topic() const { return _protected_topic; }

		bool &external_message_mode() { return _external_message_mode; }
		const bool &external_message_mode() const {
			return _external_message_mode;
		}

		bool &slot_mode() { return _slot_mode; }
		const bool &slot_mode() const { return _slot_mode; }

		uint &max_slots() { return _max_slots; }
		const uint &max_slots() const { return _max_slots; }

		bool operator==(const string &name) const;
		bool operator==(const Channel &channel) const;
};
