/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:31:15 by conobi            #+#    #+#             */
/*   Updated: 2023/01/11 15:57:07 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

#include "Bureaucrat.hpp"

/* ORTHODOX FORM COMPLIANCE */

PresidentialPardonForm::PresidentialPardonForm() {
	std::cout << BLU_FG << ITALIC
			  << "PresidentialPardonForm Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(
	const PresidentialPardonForm &val)
	: AForm(val), _target(val.getTarget()) {
	std::cout << MAG_FG << ITALIC << "PresidentialPardonForm Copy constructor "
			  << RESET << ITALIC << "called" << RESET << std::endl;
	*this = val;
}

PresidentialPardonForm::~PresidentialPardonForm() {
	std::cout << YEL_FG << ITALIC << "PresidentialPardonForm Destructor "
			  << RESET << ITALIC << "called" << RESET << std::endl;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(
	const PresidentialPardonForm &rhs) {
	std::cout << MAG_FG << ITALIC << "PresidentialPardonForm Copy assignment "
			  << RESET << ITALIC << "operator called" << RESET << std::endl;
	this->_is_signed = rhs.isSigned();
	return (*this);
}

/* ASSIGNEMENT CONSTRUCTOR */

PresidentialPardonForm::PresidentialPardonForm(const std::string name,
											   const std::string target)
	: AForm(name, 25, 5), _target(target) {
	std::cout << BLU_FG << ITALIC
			  << "PresidentialPardonForm Assignement constructor " << RESET
			  << ITALIC << "called for " << name << RESET << std::endl;
}

/* GETTERS */

std::string PresidentialPardonForm::getTarget() const {
	return (_target);
}

/* OVERRIDING EXECUTOR BASE METHOD */

void PresidentialPardonForm::_executor() const {
	std::cout << this->getTarget() << " has been pardoned by Zaphod Beeblebrox."
			  << std::endl;
}
