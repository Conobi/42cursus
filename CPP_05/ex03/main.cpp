/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:05:08 by conobi            #+#    #+#             */
/*   Updated: 2023/01/11 15:01:09 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Intern.hpp"

static void testsSingleForm(Bureaucrat &john, Bureaucrat &theo,
							Bureaucrat &bobby, AForm &AForm) {
	john.executeForm(AForm);
	theo.executeForm(AForm);
	bobby.executeForm(AForm);

	bobby.signForm(AForm);
	theo.signForm(AForm);
	john.signForm(AForm);

	john.executeForm(AForm);
	theo.executeForm(AForm);
	bobby.executeForm(AForm);
}

static void testsIntern(Bureaucrat &john, Bureaucrat &theo, Bureaucrat &bobby) {
	Intern poupi;
	AForm *test0;
	AForm *test1;
	AForm *test2;
	AForm *test3;

	std::cout << "------------------" << std::endl;
	try {
		test0 = poupi.makeForm("presidential pardon", "bobby");
		testsSingleForm(john, theo, bobby, *test0);
		delete test0;
	} catch (std::exception &e) {
		std::cerr << RED_FG << BOLD << "ERROR: " << RESET << e.what()
				  << std::endl;
	}

	std::cout << "------------------" << std::endl;
	try {
		test1 = poupi.makeForm("robotomy request", "victimos");
		testsSingleForm(john, theo, bobby, *test1);
		delete test1;
	} catch (std::exception &e) {
		std::cerr << RED_FG << BOLD << "ERROR: " << RESET << e.what()
				  << std::endl;
	}
	std::cout << "------------------" << std::endl;

	try {
		test2 = poupi.makeForm("shrubbery creation", "lumberjack");
		testsSingleForm(john, theo, bobby, *test2);
		delete test2;
	} catch (std::exception &e) {
		std::cerr << RED_FG << BOLD << "ERROR: " << RESET << e.what()
				  << std::endl;
	}

	std::cout << "------------------" << std::endl;
	try {
		test3 = poupi.makeForm("form that doesn't exist", "foobar");
		testsSingleForm(john, theo, bobby, *test3);
		delete test3;
	} catch (std::exception &e) {
		std::cerr << RED_FG << BOLD << "ERROR: " << RESET << e.what()
				  << std::endl;
	}
	std::cout << "------------------" << std::endl;
}

int main(void) {
	Bureaucrat john("John", 1);
	Bureaucrat theo("Theo", 42);
	Bureaucrat bobby("Bobby", 64);

	testsIntern(john, theo, bobby);

	return (0);
}
