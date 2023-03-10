/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Output.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:21:16 by conobi            #+#    #+#             */
/*   Updated: 2023/03/10 15:23:42 by conobi           ###   ########lyon.fr   */
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
		Output(Server &server, Client *sender, string &cmd, string &args);
		Output(Server &server, Client *sender, string &cmd,
			   vector<string> &args);
		~Output();

		operator string() const {
			return this->_output;
		}
};
