/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:30:22 by conobi            #+#    #+#             */
/*   Updated: 2023/03/08 13:42:59 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sstream>
#include <string>
#include <iostream>

namespace Utils {
template <typename T>
std::string valToString(T value) {
	std::ostringstream ss;

	ss << value;
	return ss.str();
}
}  // namespace Utils


class proutstring: public std::string {
	public:
		void prout() {
			std::cout << "prout" << std::endl;
		}

		template <typename T>
		std::string operator+(T value) {
			std::ostringstream ss;

			ss << this << value;
			return ss.str();
		}
};
