/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Output.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:21:16 by conobi            #+#    #+#             */
/*   Updated: 2023/03/15 16:59:43 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "Server.hpp"
#include "irc.hpp"

class Server;
class Client;

class Output {
	private:
		Output();
		string _output;

	public:
		Output(const Server &server, const Client *sender, const string &cmd,
			   const Client *client_arg, const string &args);
		Output(const Server &server, const Client *sender, const string &cmd,
			   const string &args);
		// Output(Server &server, Client *sender, const string &cmd,
		// 	   vector<string> &args);
		~Output();

		operator string() const { return this->_output; }
};
