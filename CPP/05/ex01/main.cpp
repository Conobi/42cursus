/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:05:08 by conobi            #+#    #+#             */
/*   Updated: 2023/01/11 15:08:32 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(int argc, char **argv) {
	if (argc == 2) {
		std::istringstream ss(argv[1]);
		int x;

		if (!(ss >> x)) {
			std::cerr << RED_FG << BOLD << "ERROR: " << RESET
					  << "Invalid number: " << argv[1] << std::endl;
		} else if (!ss.eof()) {
			std::cerr << RED_FG << BOLD << "ERROR: " << RESET
					  << "Trailing characters after number: " << argv[1]
					  << std::endl;
		} else {
			try {
				Bureaucrat john("John", 1);
				Bureaucrat theo("Theo", 42);
				Bureaucrat bobby("Bobby", 64);

				Form sell_company("Selling John's company", x, 2);
				Form sign_invoice("Invoice n°123", x, 48);
				Form accept_cookie("Accept Devil Cookies", x, 90);

				std::cout << john << std::endl;
				std::cout << theo << std::endl;
				std::cout << bobby << std::endl << std::endl;

				std::cout << sell_company << std::endl;
				std::cout << sign_invoice << std::endl;
				std::cout << accept_cookie << std::endl << std::endl;

				john.signForm(sell_company);
				theo.signForm(sign_invoice);
				bobby.signForm(accept_cookie);

				std::cout << std::endl << sell_company << std::endl;
				std::cout << sign_invoice << std::endl;
				std::cout << accept_cookie << std::endl;

			} catch (std::exception &e) {
				std::cerr << RED_FG << BOLD << "ERROR: " << RESET << e.what()
						  << std::endl;
				return (1);
			}
		}
	} else {
		std::cerr << RED_FG << BOLD << "ERROR: " << RESET
				  << "An argument is required (grade needed to sign \"Selling "
					 "John's company\" and \"Accept Devil Cookies\")."
				  << std::endl;
		return (1);
	}
	return (0);
}
