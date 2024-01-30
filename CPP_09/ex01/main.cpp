/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:32:01 by conobi            #+#    #+#             */
/*   Updated: 2023/06/01 16:37:13 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv) {
	std::string expr;
	try {
		if (argc != 2)
			throw std::runtime_error("Usage: ./rpn [expression]");
		expr = argv[1];
		RPN RPN(expr);
		return (0);
	} catch (std::exception &e) {
		std::cout << RED_FG << e.what() << RESET << std::endl;
		return (1);
	}
}
