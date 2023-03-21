/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Input.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:14:05 by conobi            #+#    #+#             */
/*   Updated: 2023/03/21 16:29:25 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Parser.hpp"
#include "irc.hpp"

class Input {
	private:
		string _tags;	  // No strong parsing rule here
		string _command;  // valid IRC command OR rpl numeric
		vector<string> _parameters;

	public:
		Input(const string &input);
		~Input();

		string &tags() { return _tags; }
		const string &tags() const { return _tags; }

		string &command() { return _command; }
		const string &command() const { return _command; }

		vector<string> &parameters() { return _parameters; }
		const vector<string> &parameters() const { return _parameters; }
};
