/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 00:03:54 by conobi            #+#    #+#             */
/*   Updated: 2022/12/26 16:31:39 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

/* ORTHODOX FORM COMPLIANCE */

Animal::Animal() {
	std::cout << BLU_FG << ITALIC
		<< "Animal Default constructor " << RESET
		<< ITALIC << "called" << RESET << std::endl;
	this->_type = "Animal";
}

Animal::Animal(const Animal &val) {
	std::cout << MAG_FG << ITALIC
		<< "Animal Copy constructor " << RESET
		<< ITALIC << "called" << RESET << std::endl;
	*this = val;
}

Animal::~Animal() {
	this->debugAddresses();
	std::cout << YEL_FG << ITALIC
	<< "Animal Destructor " << RESET
	<< ITALIC << "called" << RESET << std::endl;
}

Animal &Animal::operator=(const Animal &rhs) {
	std::cout << MAG_FG << ITALIC
	<< "Animal Copy assignment " << RESET
	<< ITALIC << "operator called" << RESET << std::endl;
	this->_type = rhs.getType();
	return (*this);
}

/* REQUIRED METHOD FOR COPY */

std::string Animal::getType() const {

	return (this->_type);
}

/* PUBLIC METHOD */

void Animal::makeSound() const {

	std::cout << "krr";
}

void Animal::debugAddresses() const {
	std::cout << "type: " << this->_type << " (" << &(this->_type) << ")" << std::endl;
	
}