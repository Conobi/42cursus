/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:23:45 by abastos           #+#    #+#             */
/*   Updated: 2023/03/08 18:42:46 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

namespace error {
const std::string needmoreparams(const std::string &command) {
	return "ERROR: Invalid command: " + command + "\r\n";
}

const std::string passwdmismatch(const std::string &pass) {
	return "464 " + pass + " :Password incorrect\r\n";
}
}  // namespace error
