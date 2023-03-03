/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:30:22 by conobi            #+#    #+#             */
/*   Updated: 2023/03/03 15:56:11 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sstream>
#include <string>

namespace Utils {
template <typename T>
std::string valToString(T value) {
	std::ostringstream ss;

	ss << value;
	return ss.str();
}
}  // namespace Utils
