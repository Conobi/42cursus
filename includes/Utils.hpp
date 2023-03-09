/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:30:22 by conobi            #+#    #+#             */
/*   Updated: 2023/03/09 01:27:54 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sstream>
#include <string>

class Utils {
	public:
		template <typename T>
		static std::string valToString(T value) {
			std::ostringstream ss;

			ss << value;
			return ss.str();
		}
};
