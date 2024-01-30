/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:33:07 by conobi            #+#    #+#             */
/*   Updated: 2023/05/31 19:36:34 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Usage: ./btc [filename]" << std::endl;
		return (1);
	}
	try {
		BitcoinExchange btc(argv[1]);
	} catch (std::exception &e) {
		std::cout << RED_FG << e.what() << RESET << std::endl;
		return (1);
	}
	return (0);
}
