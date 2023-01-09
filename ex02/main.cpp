/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:05:08 by conobi            #+#    #+#             */
/*   Updated: 2023/01/07 16:27:59 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"

void testsPresidentialPardonForm(Bureaucrat &john, Bureaucrat &theo,
								 Bureaucrat &bobby) {
	AForm *pardon_form;

	pardon_form = new PresidentialPardonForm("Sorry", "bobby");

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

	testsPresidentialPardonForm(john, theo, bobby);

	return (0);
}
