/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:23:45 by abastos           #+#    #+#             */
/*   Updated: 2023/03/02 17:20:56 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

namespace error {
  const std::string needMoreParams(const std::string &command) {
    return "ERROR: Invalid command: " + command + "\r\n";
  }
}
