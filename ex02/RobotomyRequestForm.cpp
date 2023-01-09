/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:41:42 by conobi            #+#    #+#             */
/*   Updated: 2023/01/09 19:47:31 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

#include "Bureaucrat.hpp"

/* ORTHODOX FORM COMPLIANCE */

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &val)
	: AForm(val), _target(val.getTarget()) {
	std::cout << MAG_FG << ITALIC << "RobotomyRequestForm Copy constructor "
			  << RESET << ITALIC << "called" << RESET << std::endl;
	*this = val;
}

RobotomyRequestForm::~RobotomyRequestForm() {
	std::cout << YEL_FG << ITALIC << "RobotomyRequestForm Destructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(
	const RobotomyRequestForm &rhs) {
	std::cout << MAG_FG << ITALIC << "RobotomyRequestForm Copy assignment "
			  << RESET << ITALIC << "operator called" << RESET << std::endl;
	this->_is_signed = rhs.isSigned();
	return (*this);
}

/* ASSIGNEMENT CONSTRUCTOR */

RobotomyRequestForm::RobotomyRequestForm(const std::string name,
										 const std::string target)
	: AForm(name, 25, 5), _target(target) {
	std::cout << BLU_FG << ITALIC
			  << "RobotomyRequestForm Assignement constructor " << RESET
			  << ITALIC << "called for " << name << RESET << std::endl;
}

/* GETTERS */

std::string RobotomyRequestForm::getTarget() const {
	return (_target);
}

/* OVERRIDING EXECUTOR BASE METHOD */

void RobotomyRequestForm::_executor() const {
	std::cout << "BRRRRRRRRRRRRRRRRRRRRRRRRRR" << std::endl;
	std::cout << "BRRRRRRRRRRRRRRRRRRRRRRRRRR" << std::endl;
	std::cout << "BRRRRRRRRRRRRRRRRRRRRRRRRRR" << std::endl;
}
