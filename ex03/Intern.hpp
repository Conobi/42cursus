/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:02:43 by conobi            #+#    #+#             */
/*   Updated: 2023/01/10 20:02:41 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>

#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Intern {
	private:
		static const int _nb_forms = 3;
		int _strtoFormId(std::string form_name);

	public:
		Intern();
		Intern(const Intern &val);
		~Intern();
		Intern &operator=(const Intern &rhs);

		AForm *makeForm(std::string form_name, std::string target);

		class NoFormFoundException : public std::exception {
			public:
				virtual const char *what() const throw() {
					return ("There is no form available for your request.");
				}
		};
};
