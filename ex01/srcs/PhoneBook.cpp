/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 01:10:53 by conobi            #+#    #+#             */
/*   Updated: 2022/11/27 03:44:31 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

PhoneBook::~PhoneBook() {
}

bool PhoneBook::add_contact (Contact user) {

	int i;

	if (this->_is_full()) {
		this->_push_up(user);
	} else {
		for (
			i = 0;
			this->_contacts[i].get_index() != -1 && i < 9;
			i++
		);
		this->_contacts[i] = user;
	}
	this->_contacts_created++;
	return (true);
}

void PhoneBook::list_contacts (void) const {

}

void PhoneBook::show_user (int index) const {
	std::cout << index << std::endl;
}

bool PhoneBook::_is_full(void) {

	for (int i = 0; i < 9; i++) {
		if (this->_contacts->get_index() == -1)
			return (false);
	}

	return (true);
}

bool PhoneBook::_push_up(Contact new_user) {

	for (int i = 1; i < 9; i++) {
		this->_contacts[i - 1] = this->_contacts[i];
	}
	this->_contacts[8] = new_user;
	return (true);
}
