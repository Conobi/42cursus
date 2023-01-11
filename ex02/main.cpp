/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:05:08 by conobi            #+#    #+#             */
/*   Updated: 2023/01/11 15:09:52 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

static void testsPresidentialPardonForm(Bureaucrat &john, Bureaucrat &theo,
										Bureaucrat &bobby) {
	AForm *pardon_form;

	pardon_form =
		new class PresidentialPardonForm("presidential pardon", "bobby");

	john.executeForm(*pardon_form);
	theo.executeForm(*pardon_form);
	bobby.executeForm(*pardon_form);

	bobby.signForm(*pardon_form);
	theo.signForm(*pardon_form);
	john.signForm(*pardon_form);

	john.executeForm(*pardon_form);
	theo.executeForm(*pardon_form);
	bobby.executeForm(*pardon_form);

	delete pardon_form;
}

static void testsShrubberyCreationForm(Bureaucrat &john, Bureaucrat &theo,
									   Bureaucrat &bobby) {
	AForm *pardon_form;

	pardon_form =
		new class ShrubberyCreationForm("shrubbery creation", "lumberjack");

	john.executeForm(*pardon_form);
	theo.executeForm(*pardon_form);
	bobby.executeForm(*pardon_form);

	bobby.signForm(*pardon_form);
	theo.signForm(*pardon_form);
	john.signForm(*pardon_form);

	john.executeForm(*pardon_form);
	theo.executeForm(*pardon_form);
	bobby.executeForm(*pardon_form);

	delete pardon_form;
}

static void testsRobotomyRequestForm(Bureaucrat &john, Bureaucrat &theo,
									 Bureaucrat &bobby) {
	AForm *pardon_form;

	pardon_form = new class RobotomyRequestForm("robotomy request", "Victimos");

	john.executeForm(*pardon_form);
	theo.executeForm(*pardon_form);
	bobby.executeForm(*pardon_form);

	bobby.signForm(*pardon_form);
	theo.signForm(*pardon_form);
	john.signForm(*pardon_form);

	john.executeForm(*pardon_form);
	theo.executeForm(*pardon_form);
	bobby.executeForm(*pardon_form);

	delete pardon_form;
}

int main(void) {
	Bureaucrat john("John", 1);
	Bureaucrat theo("Theo", 42);
	Bureaucrat bobby("Bobby", 64);

	std::cout << "------------------" << std::endl;
	testsPresidentialPardonForm(john, theo, bobby);
	std::cout << "------------------" << std::endl;
	testsShrubberyCreationForm(john, theo, bobby);
	std::cout << "------------------" << std::endl;
	testsRobotomyRequestForm(john, theo, bobby);
	std::cout << "------------------" << std::endl;

	return (0);
}
