/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:44:14 by conobi            #+#    #+#             */
/*   Updated: 2023/01/07 16:16:51 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

/* ORTHODOX FORM COMPLIANCE */

Bureaucrat::Bureaucrat() {
	std::cout << BLU_FG << ITALIC << "Bureaucrat Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
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

	_gradeCheck(grade);
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

/* MODIFIERS */

void Bureaucrat::increaseGrade() {
	try {
		_gradeCheck(this->getGrade() - 1);
		this->_grade--;
	} catch (std::exception &e) {
		std::cerr << RED_FG << BOLD << "ERROR: " << RESET << e.what()
				  << std::endl;
	}
}

void Bureaucrat::decreaseGrade() {
	try {
		_gradeCheck(this->getGrade() + 1);
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

void Bureaucrat::signForm(Form &Form) {
	try {
		Form.beSigned(*this);
		std::cout << this->getName() << " signed " << Form.getName()
				  << std::endl;
	} catch (Form::GradeTooLowException &e) {
		std::cout << this->getName() << " couldn't sign " << Form.getName()
				  << " because its grade was too low" << std::endl;
	}
}

/* << OPERATOR OVERLOAD */

std::ostream &operator<<(std::ostream &os, const Bureaucrat &val) {
	os << val.getName() << ", bureaucrat grade " << val.getGrade() << ".";
	return (os);
}
