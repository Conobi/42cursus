/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:51:00 by abastos           #+#    #+#             */
/*   Updated: 2023/03/08 14:40:09 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

namespace rpl {
  const std::string welcome(const std::string &server, const std::string &nick) {
    return ":" + server + " 001 " + nick + " :Welcome to the Internet Relay Network " + nick + "\r\n";
  }
}
