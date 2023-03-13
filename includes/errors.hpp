/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:23:45 by abastos           #+#    #+#             */
/*   Updated: 2023/03/09 19:48:08 by abastos          ###   ########lyon.fr   */
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

		static const std::string alreadyregistered() {
			return "462 * :You may not reregister\r\n";
		}

		static const std::string nonicknamegiven() {
			return "431 :Invalid nickname\r\n";
		}

		static const std::string oneusnickname(const std::string &nick) {
			return "432 " + nick + " :Erroneus nickname\r\n";
		}

		static const std::string nicknameinuse(const std::string &nick) {
			return "433 " + nick + " :Nickname is already in use\r\n";
		}

		static const std::string nickcollision(const std::string &nick) {
			return "436 " + nick + " :Nickname collision KILL\r\n";
		}
};
