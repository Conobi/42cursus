/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:20:29 by conobi            #+#    #+#             */
/*   Updated: 2022/11/27 04:52:56 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

static void welcome_print(void) {
	std::cout << MAG_FG
		<< ";-.  .               ,-.          ,   " << std::endl
		<< "|  ) |               |  )         |   " << std::endl
		<< "|-'  |-. ,-. ;-. ,-. |-<  ,-. ,-. | , " << std::endl
		<< "|    | | | | | | |-' |  ) | | | | |<  " << std::endl
		<< "'    ' ' `-' ' ' `-' `-'  `-' `-' ' ` " << std::endl
		<< RESET << std::endl
		<< UNDERLINE << "Commands available: " << std::endl << RESET
		<< BLU_FG << "(ADD | SEARCH | EXIT)" << std::endl << std::endl;
}

int main (void) {

	PhoneBook book;

	welcome_print();
	Steps::prompter("Command", book, Steps::command_manager);
	return (0);
}
