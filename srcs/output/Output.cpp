/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Output.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:30:56 by conobi            #+#    #+#             */
/*   Updated: 2023/03/15 17:03:16 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Output.hpp"

Output::Output(const Server &server, const Client *sender, const string &cmd,
			   const Client *client_arg, const string &args)
	: _output("") {
	string source = "";

	if (sender && sender->authStatus() == REGISTERED) {
		source =
			":" + sender->nick() + "!" + sender->username() + "/" + server.ip();
	} else {
		source = ":" + server.ip();
	}

	this->_output =
		(source.empty() ? "" : source + " ") + (cmd.empty() ? "" : cmd + " ") +
		(!client_arg ? "" : client_arg->nick() + " ") + args + "\r\n";
}

Output::Output(const Server &server, const Client *sender, const string &cmd,
			   const string &args)
	: _output("") {
	this->_output = Output(server, sender, cmd, NULL, args);
}

// Output::Output(Server &server, Client *sender, const string &cmd,
// vector<string>&args) : _output("") { 	string args_concat = "";

// 	for (vector<string>::iterator it = args.begin(); it != args.end(); ++it) {
// 		if (it == args.end() - 1)
// 			args_concat += ":" + *it;
// 		else
// 			args_concat += *it + " ";
// 	}

// 	Output(server, sender, cmd, args_concat);
// }

Output::~Output() {
}
