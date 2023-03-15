/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:27:41 by conobi            #+#    #+#             */
/*   Updated: 2023/03/14 18:31:19 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"

class Parser {
	public:
		static vector<string> parseCommas(string comma_string);
		static bool isNickValid(const string &nick);
		static bool isChannelValid(const string &channel);
};
