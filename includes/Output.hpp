/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Output.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:21:16 by conobi            #+#    #+#             */
/*   Updated: 2023/03/11 17:13:22 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "Server.hpp"
#include "irc.hpp"

class Output {
	private:
		Output();
		string _output;

	public:
		Output(Server &server, Client *sender, const string &cmd, const string &args);
		Output(Server &server, Client *sender, const string &cmd, vector<string> &args);
		~Output();

		operator string() const {
			return this->_output;
		}
};
