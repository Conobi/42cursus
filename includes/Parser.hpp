/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:27:41 by conobi            #+#    #+#             */
/*   Updated: 2023/03/10 15:41:07 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"

class Parser {
	public:
		static vector<string> parseCommas(string comma_string);
		static bool isNickValid(const string &nick);
};
