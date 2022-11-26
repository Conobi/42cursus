/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:41:12 by conobi            #+#    #+#             */
/*   Updated: 2022/11/26 23:22:52 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact(): _index(-1) {
}

Contact::~Contact()
{
}

bool Contact::is_valid (void) const {
	return (true);
}

bool Contact::set_first_name (std::string str) {
	if (str.length() > 0)
		this->_first_name = str;
	else
		return (false);
	return (true);
}

std::string Contact::get_first_name (void) const {
	return (this->_first_name);
}

bool Contact::set_last_name (std::string str) {
	if (str.length() > 0)
		this->_last_name = str;
	else
		return (false);
	return (true);
}

std::string Contact::get_last_name (void) const {
	return (this->_last_name);
}

bool Contact::set_nickname (std::string str) {
	if (str.length() > 0)
		this->_nickname = str;
	else
		return (false);
	return (true);
}

std::string Contact::get_nickname (void) const {
	return (this->_nickname);
}

std::string Contact::get_name (void) const {
	if (this->get_nickname().length() > 0)
		return (
			this->get_first_name() + " " + this->get_last_name()
			+ " (" + this->get_nickname() + ")"
		);
	else if (this->get_last_name().length() > 0)
		return (
			this->get_first_name() + " " + this->get_last_name()
		);
	else
		return (
			this->get_first_name()
		);
}

bool Contact::set_phone_number (std::string str) {
	if (str.length() > 0)
		this->_phone_number = str;
	else
		return (false);
	return (true);
}

std::string Contact::get_phone_number (void) const {
	return (this->_phone_number);
}

bool Contact::set_secret (std::string str) {
	if (str.length() > 0)
		this->_secret = str;
	else
		return (false);
	return (true);
}

std::string Contact::get_secret (void) const {
	return (this->_secret);
}

bool Contact::set_index (int index) {
	if (index >= 0 || index < 9)
		this->_index = index;
	else
		return (false);
	return (true);
}

int Contact::get_index (void) const {
	return (this->_index);
}
