/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:41:12 by conobi            #+#    #+#             */
/*   Updated: 2022/11/27 05:25:05 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

Contact::Contact(): _index(-1) {
}

Contact::~Contact()
{
}

bool Contact::is_valid (void) const {
	return (true);
}

bool Contact::set_first_name (std::string str) {
	str = this->trim(str);
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
	str = this->trim(str);
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
	str = this->trim(str);
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
	str = this->trim(str);

	if (str.length() > 0) {
		if (this->is_valid_phone_number(str)) {
			this->_phone_number = str;
			return (true);
		} else
			std::cerr << RED_FG
			<< "The phone number you entered is in an invalid format. Try again."
			<< RESET << std::endl;
	}
	return (false);
}

std::string Contact::get_phone_number (void) const {
	return (this->_phone_number);
}

bool Contact::set_secret (std::string str) {
	str = this->trim(str);
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

std::string Contact::trim(std::string str) {

	size_t len;
	size_t start;

	start = str.find_first_not_of(" \t\n\v\f\r");
	if (start > str.length() - 1)
		start = 0;
	len = str.find_last_not_of(" \t\n\v\f\r") - start + 1;
	if (len > str.length())
		len = 0;
	return (str.substr(start, len));
}

bool Contact::is_valid_phone_number(std::string str) {
	size_t i;

	i = 0;
	while (
		(str[i] == '+'
		|| str[i] == ' '
		|| str[i] == ' '
		|| (str[i] >= '0' && str[i] <= '9'))
		&& i < str.length()
	)
		i++;
	if (i < str.length())
		return (false);
	return (true);
}
