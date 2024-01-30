/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:30:22 by conobi            #+#    #+#             */
/*   Updated: 2023/03/20 14:40:43 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "irc.hpp"

class Utils {
	public:
		template <typename T>
		static std::string valToString(T value) {
			std::ostringstream ss;

			ss << value;
			return ss.str();
		}

		static std::string toLower(std::string str) {
			std::transform(str.begin(), str.end(), str.begin(), ::tolower);
			return str;
		}

		static std::string toUpper(std::string str) {
			std::transform(str.begin(), str.end(), str.begin(), ::toupper);
			return str;
		}
};
