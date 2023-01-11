/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:07:51 by conobi            #+#    #+#             */
/*   Updated: 2023/01/11 16:23:32 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

/* ORTHODOX FORM COMPLIANCE */

Intern::Intern() {
	std::cout << BLU_FG << ITALIC << "Intern Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
}

Intern::Intern(const Intern &val) {
	std::cout << MAG_FG << ITALIC << "Intern Copy constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	*this = val;
}

Intern::~Intern() {
	std::cout << YEL_FG << ITALIC << "Intern Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

Intern &Intern::operator=(const Intern &rhs) {
	std::cout << MAG_FG << ITALIC << "Intern Copy assignment " << RESET
			  << ITALIC << "operator called" << RESET << std::endl;
	(void)rhs;
	return (*this);
}

int Intern::_strtoFormId(std::string form_name) {
	std::string form_str_list[] = {"presidential pardon", "shrubbery creation",
								   "robotomy request"};

	for (int i = 0; i < this->_nb_forms; i++) {
		if (form_name == form_str_list[i])
			return (i);
	}
	return (-1);
}

AForm *Intern::makeForm(std::string form_name, std::string target) {
	AForm *Form;
	int id;

	id = this->_strtoFormId(form_name);

	std::cout << "Intern creates " << form_name << std::endl;

	switch (id) {
		case 0:
			Form = new PresidentialPardonForm(target);
			break;
		case 1:
			Form = new ShrubberyCreationForm(target);
			break;

		case 2:
			Form = new RobotomyRequestForm(target);
			break;

		default:
			throw Intern::NoFormFoundException();
			break;
	}

	return (Form);
}