/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:05:08 by conobi            #+#    #+#             */
/*   Updated: 2023/01/09 14:46:45 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"

static void testsPresidentialPardonForm(Bureaucrat &john, Bureaucrat &theo,
										Bureaucrat &bobby) {
	AForm *pardon_form;

	pardon_form = new class PresidentialPardonForm("Sorry", "bobby");

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

	pardon_form = new class ShrubberyCreationForm("Oak", "lumberjack");

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

	return (0);
}
