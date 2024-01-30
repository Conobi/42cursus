/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:53:52 by conobi            #+#    #+#             */
/*   Updated: 2022/12/05 16:28:06 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main (void) {
	Harl logger;

	std::cout << "DEBUG STRING: " << std::endl;
	logger.complain("DEBUG");
	std::cout << "INFO STRING: " << std::endl;
	logger.complain("INFO");
	std::cout << "WARNING STRING: " << std::endl;
	logger.complain("WARNING");
	std::cout << "ERROR STRING: " << std::endl;
	logger.complain("ERROR");

	return (0);
}
