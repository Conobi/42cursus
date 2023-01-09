/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:59:52 by conobi            #+#    #+#             */
/*   Updated: 2023/01/07 15:17:24 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

#include "Bureaucrat.hpp"

/* ORTHODOX FORM COMPLIANCE */

Form::Form(const Form &val)
	: _name(val.getName()),
	  _grade_to_sign(val.getGradeToSign()),
	  _grade_to_exec(val.getGradeToExec()) {
	std::cout << MAG_FG << ITALIC << "Form Copy constructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
	*this = val;
}

Form::~Form() {
	std::cout << YEL_FG << ITALIC << "Form Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

Form &Form::operator=(const Form &rhs) {
	std::cout << MAG_FG << ITALIC << "Form Copy assignment " << RESET << ITALIC
			  << "operator called" << RESET << std::endl;
	this->_is_signed = rhs.isSigned();
	return (*this);
}

/* ASSIGNEMENT CONSTRUCTOR */

Form::Form(const std::string name, const unsigned short grade_to_sign,
		   const unsigned short grade_to_exec)
	: _name(name),
	  _grade_to_sign(grade_to_sign),
	  _grade_to_exec(grade_to_exec),
	  _is_signed(false) {
	std::cout << BLU_FG << ITALIC << "Form Assignement constructor " << RESET
			  << ITALIC << "called for " << name << RESET << std::endl;

	_gradeCheck(grade_to_sign);
	_gradeCheck(grade_to_exec);
}

/* GETTERS */
std::string Form::getName() const {
	return (_name);
}

unsigned short Form::getGradeToSign() const {
	return (_grade_to_sign);
}

unsigned short Form::getGradeToExec() const {
	return (_grade_to_exec);
}

bool Form::isSigned() const {
	return (_is_signed);
}

/* MODIFIERS */

void Form::beSigned(Bureaucrat &Bureaucrat) {
	if (Bureaucrat.getGrade() > this->getGradeToSign()) {
		throw Form::GradeTooLowException();
	} else {
		this->_is_signed = true;
	}
}

/* PRIVATE METHODS */

void Form::_gradeCheck(const unsigned short new_grade) {
	if (new_grade < 1)
		throw Form::GradeTooHighException();

	else if (new_grade > 150)
		throw Form::GradeTooLowException();
}

/* << OPERATOR OVERLOAD */

std::ostream &operator<<(std::ostream &os, const Form &val) {
	os << "Form \"" << val.getName() << "\" is "
	   << (val.isSigned() ? "signed" : "not signed")
	   << ". The Form needs grade " << val.getGradeToExec()
	   << " to be executed and grade " << val.getGradeToSign()
	   << " to be signed.";
	return (os);
}
