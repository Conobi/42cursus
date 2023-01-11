/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:44:14 by conobi            #+#    #+#             */
/*   Updated: 2023/01/11 15:50:44 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

#include <exception>

/* ORTHODOX FORM COMPLIANCE */

Bureaucrat::Bureaucrat() : _name("Undefined name"), _grade(150) {
	std::cout << BLU_FG << ITALIC << "Bureaucrat Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	this->_gradeCheck(this->_grade);
}

Bureaucrat::Bureaucrat(const Bureaucrat &val) {
	std::cout << MAG_FG << ITALIC << "Bureaucrat Copy constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	*this = val;
}

Bureaucrat::~Bureaucrat() {
	std::cout << YEL_FG << ITALIC << "Bureaucrat Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &rhs) {
	std::cout << MAG_FG << ITALIC << "Bureaucrat Copy assignment " << RESET
			  << ITALIC << "operator called" << RESET << std::endl;
	this->_name = rhs.getName();
	this->_grade = rhs.getGrade();
	return (*this);
}

/* ASSIGNEMENT CONSTRUCTOR */

Bureaucrat::Bureaucrat(const std::string name, const unsigned short grade)
	: _name(name) {
	std::cout << BLU_FG << ITALIC << "Bureaucrat Assignement constructor "
			  << RESET << ITALIC << "called for " << name << RESET << std::endl;

	this->_gradeCheck(grade);
	this->_grade = grade;
}

/* GETTERS */
std::string Bureaucrat::getName() const {
	return (_name);
}

unsigned short Bureaucrat::getGrade() const {
	return (_grade);
}

/* MODIFIERS */

void Bureaucrat::increaseGrade() {
	try {
		this->_gradeCheck(this->getGrade() - 1);
		this->_grade--;
	} catch (std::exception &e) {
		std::cerr << RED_FG << BOLD << "ERROR: " << RESET << e.what()
				  << std::endl;
	}
}

void Bureaucrat::decreaseGrade() {
	try {
		this->_gradeCheck(this->getGrade() + 1);
		this->_grade++;
	} catch (std::exception &e) {
		std::cerr << RED_FG << BOLD << "ERROR: " << RESET << e.what()
				  << std::endl;
	}
}

/* PRIVATE METHODS */

void Bureaucrat::_gradeCheck(const unsigned short new_grade) {
	if (new_grade < 1)
		throw Bureaucrat::GradeTooHighException();

	else if (new_grade > 150)
		throw Bureaucrat::GradeTooLowException();
}

/* PUBLIC METHODS */

void Bureaucrat::signForm(AForm &AForm) {
	try {
		AForm.beSigned(*this);
		std::cout << this->getName() << " signed " << AForm.getName()
				  << std::endl;
	} catch (AForm::SignGradeTooLowException &e) {
		std::cout << this->getName() << " couldn't sign " << AForm.getName()
				  << " because its grade was too low" << std::endl;
	}
}

void Bureaucrat::executeForm(AForm &AForm) {
	try {
		AForm.execute(*this);
		std::cout << this->getName() << " executed " << AForm.getName()
				  << std::endl;
	} catch (std::exception &e) {
		std::cout << this->getName() << " couldn't execute " << AForm.getName()
				  << ". " << e.what() << std::endl;
	}
}

/* << OPERATOR OVERLOAD */

std::ostream &operator<<(std::ostream &os, const Bureaucrat &val) {
	os << val.getName() << ", bureaucrat grade " << val.getGrade() << ".";
	return (os);
}
