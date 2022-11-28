/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 01:10:53 by conobi            #+#    #+#             */
/*   Updated: 2022/11/28 17:29:42 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

PhoneBook::~PhoneBook() {
}

bool PhoneBook::_add_contact (Contact *user) {

	int i;

	if (this->_is_full()) {
		user->set_index(this->_contacts_created);
		this->_push_up(user);
	} else {
		for (
			i = 0;
			this->_contacts[i].get_index() != -1 && i < 9;
			i++
		);
		user->set_index(this->_contacts_created);
		this->_contacts[i] = *user;
	}
	this->_contacts_created += 1;
	return (true);
}

bool PhoneBook::_list_contacts (void) const {

	if (this->_contacts[0].get_index() == -1) {
		std::cerr << RED_FG <<
			"The phone book is currently empty. Enter a contact before using this command."
			<< RESET << std::endl;
		return (false);
	}
	std::cout << BOLD << CYN_FG
		<< std::setw(10) << "No."
		<< " | " << std::setw(10) << "First name"
		<< " | " << std::setw(10) << "Last name"
		<< " | " << std::setw(10) << "Nickname"
		<< std::endl << RESET;

	for (size_t i = 0; i < 9 && this->_contacts[i].get_index() != -1; i++) {
		std::cout
			<< std::setw(10) << this->_contacts[i].get_index() + 1
			<< " | " << std::setw(10) << this->_cut_dot(this->_contacts[i].get_first_name(), 10)
			<< " | " << std::setw(10) << this->_cut_dot(this->_contacts[i].get_last_name(), 10)
			<< " | " << std::setw(10) << this->_cut_dot(this->_contacts[i].get_nickname(), 10)
			<< std::endl;
	}
	return (true);
}

Contact *PhoneBook::_find_user (int index) {
	for (size_t i = 0; i < 9 && index >= 0; i++) {
		if (this->_contacts[i].get_index() == index)
			return (&(this->_contacts[i]));
	}

	std::cerr << RED_FG
		<< "No user has been found matching this id."
		<< RESET << std::endl;

	return (NULL);
}

void PhoneBook::_show_user (Contact *user) const {
	std::cout
		<< MAG_FG << BOLD << "First name :" << RESET << std::endl
		<< user->get_first_name() << std::endl << std::endl
		<< MAG_FG << BOLD << "Last name :" << RESET << std::endl
		<< user->get_last_name() << std::endl << std::endl
		<< MAG_FG << BOLD << "Nickname :" << RESET << std::endl
		<< user->get_nickname() << std::endl << std::endl
		<< MAG_FG << BOLD << "Phone number :" << RESET << std::endl
		<< user->get_phone_number() << std::endl << std::endl
		<< MAG_FG << BOLD << "Secret :" << RESET << std::endl
		<< ITALIC << user->get_secret() << RESET << std::endl;
}

bool PhoneBook::_is_full(void) {

	for (int i = 0; i < 9; i++) {
		if (this->_contacts[i].get_index() == -1) {
			return (false);
		}
	}
	return (true);
}

bool PhoneBook::_push_up(Contact *new_user) {

	for (int i = 1; i < 9; i++) {
		this->_contacts[i - 1] = this->_contacts[i];
	}
	this->_contacts[8] = *new_user;
	return (true);
}

std::string PhoneBook::_cut_dot(std::string str, size_t length) const {
	std::string ret;

	ret = str;
	if (ret.length() > length) {
		ret = ret.substr(0, length);
		ret[length - 1] = '.';
	}
	return (ret);
}

bool PhoneBook::_command_manager(const std::string input) {

	if (input == "ADD") {
		PhoneBook::_add_manager();
	}
	else if (input == "SEARCH") {
		PhoneBook::_search_manager();
	}
	else if (input == "EXIT") {
		std::cout << "Goodbye." << std::endl;
		return (false);
	}
	else
		std::cerr << RED_FG
		<< "Command invalid. Retry."
		<< RESET << std::endl;
	return (true);
}

bool PhoneBook::_add_manager(void) {

	Contact	new_user;

	this->_add_prompter("Enter a first name", &new_user, &Contact::set_first_name);
	this->_add_prompter(new_user.get_name() + "'s last name", &new_user, &Contact::set_last_name);
	this->_add_prompter(new_user.get_name() + "'s nickname", &new_user, &Contact::set_nickname);
	this->_add_prompter(new_user.get_name() + "'s phone number", &new_user, &Contact::set_phone_number);
	this->_add_prompter(new_user.get_name() + "'s secret", &new_user, &Contact::set_secret);

	this->_add_contact(&new_user);

	return (true);
}

bool PhoneBook::_search_manager(void) {

	if (this->_list_contacts())
		this->_search_prompter("Enter an index");

	return (true);
}

void PhoneBook::prompter (const std::string prompt)
{
	std::string input;

	std::cout << GRN_FG << UNDERLINE
		<< prompt << RESET << GRN_FG << ": " << RESET;
	while (std::getline(std::cin, input)) {
		if (input.length()) {
			if (!this->_command_manager(input))
				break ;
		}
		if (std::cin.eof()) {
			std::cout << "CTRL+D given. We leave the program, goodbye!" << std::endl;
			return ;
		}
		std::cout << GRN_FG << UNDERLINE
			<< prompt << RESET << GRN_FG << ": " << RESET;
	}
	std::cout << std::endl;
}

void PhoneBook::_add_prompter (
	const std::string prompt,
	Contact	*new_user,
	bool (Contact::*manager)(std::string)
) {
	std::string input;

	if (std::cin.eof())
		return ;

	std::cout << CYN_FG << UNDERLINE
		<< prompt << RESET << CYN_FG << ": " << RESET;
	while (std::getline(std::cin, input)) {
		if (input.length()) {
			if ((*new_user.*manager)(input))
				break ;
		}
		std::cout << CYN_FG << UNDERLINE
			<< prompt << RESET << CYN_FG << ": " << RESET;
	}

}


void PhoneBook::_search_prompter (const std::string prompt)
{
	std::string input;
	int index;
	Contact *user_to_find;

	if (std::cin.eof())
		return ;

	std::cout << CYN_FG << UNDERLINE
		<< prompt << RESET << CYN_FG << ": " << RESET;

	while (std::getline(std::cin, input)) {
		if (input.length()) {
			index = -1;
			std::istringstream(input) >> index;
			user_to_find = this->_find_user(index - 1);
			if (user_to_find != NULL) {
				this->_show_user(user_to_find);
				break ;
			}
		}
		std::cout << CYN_FG << UNDERLINE
			<< prompt << RESET << CYN_FG << ": " << RESET;
	}
}
