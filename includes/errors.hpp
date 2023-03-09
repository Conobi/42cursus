/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:23:45 by abastos           #+#    #+#             */
/*   Updated: 2023/03/09 13:31:21 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Error {
	public:
		Error() {}

		static const std::string needmoreparams(const std::string &command) {
			return "ERROR: Invalid command: " + command + "\r\n";
		}

		static const std::string passwdmismatch(const std::string &pass) {
			return "464 " + pass + " :Password incorrect\r\n";
		}
};
