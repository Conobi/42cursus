/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 00:35:54 by conobi            #+#    #+#             */
/*   Updated: 2023/03/09 02:23:14 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "Logger.hpp"
#include "Utils.hpp"
#include "irc.hpp"

// Created on user join, deleted when the last user leaves.
// First char MUST be a #, and a channel name cannot contains any spaces,
// 0x07/CTRL^D/BELL or commas.
// The user creating the channel become the OP.
// A channel contains a TOPIC
// Warning: What to do when the OP leaves the channel?

class Channel {
	private:
		Channel();

		map<Client, int> _users;

		vector<Client> _invite_list;
		string _password;
		vector<Client> _ban_list;
		uint _max_slots;
		string _topic;

		bool _invite_list_mode;
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
		void setRole(const Client &client, const uint &role);

		void setTopic(const Client &client, const string &topic);

		void setMode(const Client &client, const string &modestring);

		void sendMessage(const Client &sender, const uint &role,
						 const string &message);

		bool containsClient(const Client &client);

		static bool isValidChannelName(const string &channel_name);
};
