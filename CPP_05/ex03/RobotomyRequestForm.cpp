/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:41:42 by conobi            #+#    #+#             */
/*   Updated: 2023/01/11 16:20:30 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

#include <ctime>

#include "Bureaucrat.hpp"

/* ORTHODOX FORM COMPLIANCE */

RobotomyRequestForm::RobotomyRequestForm() {
	std::cout << BLU_FG << ITALIC << "RobotomyRequestForm Default constructor "
			  << RESET << ITALIC << "called" << RESET << std::endl;
}

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

RobotomyRequestForm::RobotomyRequestForm(const std::string target)
	: AForm("robotomy request", 25, 5), _target(target) {
	std::cout << BLU_FG << ITALIC
			  << "RobotomyRequestForm Assignement constructor " << RESET
			  << ITALIC << "called for " << this->getName() << RESET << std::endl;
}

/* GETTERS */

std::string RobotomyRequestForm::getTarget() const {
	return (_target);
}

/* OVERRIDING EXECUTOR BASE METHOD */

void RobotomyRequestForm::_executor() const {
	std::time_t t = std::time(0);

	std::cout << "BRRRRRRRRRRRRRRRRRRRRRRRRRR" << std::endl;
	std::cout << "BRRRRRRRRRRRRRRRRRRRRRRRRRR" << std::endl;
	std::cout << "BRRRRRRRRRRRRRRRRRRRRRRRRRR" << std::endl;

	if (t % 2) {
		std::cout << GRN_FG << BOLD << "SUCCESS: " << RESET << this->getTarget()
				  << " has been robotomized." << std::endl;
	} else {
		std::cout << RED_FG << BOLD << "FAILURE: " << RESET
				  << "The robotomy of " << this->getTarget()
				  << " has failed. Oops." << std::endl;
	}
}
