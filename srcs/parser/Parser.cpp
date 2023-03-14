/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:27:00 by conobi            #+#    #+#             */
/*   Updated: 2023/03/14 15:45:09 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

vector<string> Parser::parseCommas(string comma_string) {
	vector<string> strings_array;

	// Separate the string in a vector of string, for each comma found.
	while (comma_string.find(',') != string::npos) {
		strings_array.push_back(comma_string.substr(0, comma_string.find(',')));
		comma_string.erase(0, comma_string.find(',') + 1);
	}
	strings_array.push_back(comma_string);

	return strings_array;
}

bool Parser::isNickValid(const string &nick) {
	string charset = " ,*?!@$:.#&";
	if (nick.empty())
		return false;
	for (size_t i = 0; i < nick.size(); i++) {
		if (!isalnum(nick[i]) && charset.find(nick[i]) != string::npos)
			return false;
	}
	return true;
}
