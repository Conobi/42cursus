/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:07:51 by conobi            #+#    #+#             */
/*   Updated: 2023/01/11 18:27:45 by conobi           ###   ########lyon.fr   */
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

/* PRIVATE METHODS */

int Intern::_strtoFormId(std::string form_name) {
	std::string form_str_list[] = {"presidential pardon", "shrubbery creation",
								   "robotomy request"};

	for (int i = 0; i < this->_nb_forms; i++) {
		if (form_name == form_str_list[i])
			return (i);
	}
	return (-1);
}

AForm *Intern::_makePresidentialPardonForm(std::string target) {
	return (new PresidentialPardonForm(target));
}

AForm *Intern::_makeShruberryCreationForm(std::string target) {
	return (new ShrubberyCreationForm(target));
}

AForm *Intern::_makeRobotomyRequestForm(std::string target) {
	return (new RobotomyRequestForm(target));
}

AForm *Intern::makeForm(std::string form_name, std::string target) {
	AForm *(Intern::*_func_arr[3])(std::string) = {
		&Intern::_makePresidentialPardonForm,
		&Intern::_makeShruberryCreationForm, &Intern::_makeRobotomyRequestForm};
	int id = this->_strtoFormId(form_name);

	std::cout << "Intern creates " << form_name << std::endl;

	if (id >= 0) {
		return ((this->*_func_arr[id])(target));
	}
	throw Intern::NoFormFoundException();
	return (NULL);
}