/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:59:52 by conobi            #+#    #+#             */
/*   Updated: 2023/01/11 15:55:18 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

#include "Bureaucrat.hpp"

/* ORTHODOX FORM COMPLIANCE */

AForm::AForm()
	: _name("Undefined Form"),
	  _grade_to_sign(150),
	  _grade_to_exec(150),
	  _is_signed(false) {
	std::cout << BLU_FG << ITALIC << "Form Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;

	this->_gradeCheck(this->_grade_to_sign);
	this->_gradeCheck(this->_grade_to_exec);
}

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

	this->_gradeCheck(grade_to_sign);
	this->_gradeCheck(grade_to_exec);
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

void AForm::beSigned(Bureaucrat &Bureaucrat) {
	if (Bureaucrat.getGrade() > this->getGradeToSign()) {
		throw AForm::SignGradeTooLowException();
	} else {
		this->_is_signed = true;
	}
}

/* PRIVATE METHODS */

void AForm::_gradeCheck(const unsigned short grade) {
	if (grade < 1 || grade > 150)
		throw AForm::GradeOutOfBoundException();
}

void AForm::execute(const Bureaucrat &Bureaucrat) const {
	if (Bureaucrat.getGrade() > this->getGradeToSign()) {
		throw AForm::ExecGradeTooLowException();
	} else if (!this->isSigned()) {
		throw AForm::UnsignedFormExecutedException();
	} else {
		this->_executor();
	}
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
