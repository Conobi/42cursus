/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:05:08 by conobi            #+#    #+#             */
/*   Updated: 2023/01/04 19:59:10 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

                Form toast;

                std::cout << john << std::endl;
                std::cout << theo << std::endl;
                std::cout << bobby << std::endl;

                john.decreaseGrade();
                std::cout << john << std::endl;
                theo.increaseGrade();
                std::cout << theo << std::endl;

                bobby.increaseGrade();
                std::cout << bobby << std::endl;
                bobby.decreaseGrade();
                std::cout << bobby << std::endl;
                bobby.decreaseGrade();
                std::cout << bobby << std::endl;

            } catch (std::exception &e) {
                std::cerr << RED_FG << BOLD << "ERROR: " << RESET << e.what()
                          << std::endl;
                return (1);
            }
        }
    } else {
        std::cerr << RED_FG << BOLD << "ERROR: " << RESET
                  << "An argument is required (Bobby's grade)." << std::endl;
        return (1);
    }
    return (0);
}