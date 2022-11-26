/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Steps.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 02:46:04 by conobi            #+#    #+#             */
/*   Updated: 2022/11/26 06:08:16 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Steps.hpp"
#include "Contact.hpp"

void Steps::prompter (
	const std::string prompt,
	PhoneBook book,
	bool (*manager)(std::string, PhoneBook)
)
{
	std::string input;

	std::cout << prompt << " : ";
	/* While we don't match EOF or > string */
	while (std::getline(std::cin, input)) {
		if (input.length()) {
			if (!manager(input, book))
				break ;
		}
		std::cout << prompt << " : ";
	}
	std::cout << std::endl;
}

bool Steps::command_manager(const std::string input, PhoneBook book) {

	if (input == "ADD") {
		Steps::add_manager(book);
		std::cout << "ADD command to implement" << std::endl;
	}
	else if (input == "SEARCH")
		std::cout << "SEARCH command to implement" << std::endl;
	else if (input == "EXIT") {
		std::cout << "Command EXIT implemented. Goodbye." << std::endl;
		return (false);
	}
	else
		std::cout << "Command invalid. Retry." << std::endl;
	return (true);
}

void Steps::add_prompter (
	const std::string prompt,
	Contact	new_user,
	bool (Contact::*manager)(std::string)
)
{
	std::string input;

	std::cout << prompt << " : ";
	/* While we don't match EOF or > string */
	while (std::getline(std::cin, input)) {
		if (input.length()) {
			if (!(new_user.*manager)(input))
				break ;
		}
		std::cout << prompt << " : ";
	}
	std::cout << std::endl;
}


bool Steps::add_manager(PhoneBook book) {

	Contact	new_user;

	Steps::add_prompter("Enter a first name", new_user, &Contact::set_first_name);

	book.add_contact(new_user);
	return (true);
}
