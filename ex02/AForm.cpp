/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:59:52 by conobi            #+#    #+#             */
/*   Updated: 2023/01/06 18:26:23 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

#include "Bureaucrat.hpp"

/* ORTHODOX FORM COMPLIANCE */

AForm::AForm(const AForm &val)
	: _name(val.getName()),
	  _grade_to_sign(val.getGradeToSign()),
	  _grade_to_exec(val.getGradeToExec()) {
	std::cout << MAG_FG << ITALIC << "AForm Copy constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	*this = val;
}

AForm::~AForm() {
	std::cout << YEL_FG << ITALIC << "AForm Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

AForm &AForm::operator=(const AForm &rhs) {
	std::cout << MAG_FG << ITALIC << "AForm Copy assignment " << RESET << ITALIC
			  << "operator called" << RESET << std::endl;
	this->_is_signed = rhs.isSigned();
	return (*this);
}

/* ASSIGNEMENT CONSTRUCTOR */

AForm::AForm(const std::string name, const unsigned short grade_to_sign,
			 const unsigned short grade_to_exec)
	: _name(name),
	  _grade_to_sign(grade_to_sign),
	  _grade_to_exec(grade_to_exec),
	  _is_signed(false) {
	std::cout << BLU_FG << ITALIC << "AForm Assignement constructor " << RESET
			  << ITALIC << "called for " << name << RESET << std::endl;

	_gradeCheck(grade_to_sign);
	_gradeCheck(grade_to_exec);
}

/* GETTERS */
std::string AForm::getName() const {
	return (_name);
}

unsigned short AForm::getGradeToSign() const {
	return (_grade_to_sign);
}

unsigned short AForm::getGradeToExec() const {
	return (_grade_to_exec);
}

bool AForm::isSigned() const {
	return (_is_signed);
}

/* MODIFIERS */

void AForm::beSigned(Bureaucrat &person) {
	if (person.getGrade() > this->getGradeToSign()) {
		throw AForm::GradeTooLowException();
	} else {
		this->_is_signed = true;
	}
}

/* PRIVATE METHODS */

void AForm::_gradeCheck(const unsigned short new_grade) {
	if (new_grade < 1)
		throw AForm::GradeTooHighException();

	else if (new_grade > 150)
		throw AForm::GradeTooLowException();
}

/* << OPERATOR OVERLOAD */

std::ostream &operator<<(std::ostream &os, const AForm &val) {
	os << "Form \"" << val.getName() << "\" is "
	   << (val.isSigned() ? "signed" : "not signed")
	   << ". The Form needs grade " << val.getGradeToExec()
	   << " to be executed and grade " << val.getGradeToSign()
	   << " to be signed.";
	return (os);
}
