/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SystemException.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:54:20 by conobi            #+#    #+#             */
/*   Updated: 2023/02/22 18:12:50 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>
#include <string>

using namespace std;

class SystemException : public exception {
	private:
		using exception::what;
		const char* _message;

	public:
		SystemException(const string& msg) : _message(msg.c_str()) {
		}

		virtual const char* what() const throw() {
			return _message;
		}
};
