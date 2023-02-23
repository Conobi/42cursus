/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:30:22 by conobi            #+#    #+#             */
/*   Updated: 2023/02/23 17:18:27 by conobi           ###   ########lyon.fr   */
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
