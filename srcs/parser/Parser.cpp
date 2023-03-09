/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:27:00 by conobi            #+#    #+#             */
/*   Updated: 2023/03/09 18:48:09 by conobi           ###   ########lyon.fr   */
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
