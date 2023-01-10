/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:13:44 by conobi            #+#    #+#             */
/*   Updated: 2023/01/06 02:05:50 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

/* ORTHODOX FORM COMPLIANCE */

Dog::Dog() {
	std::cout << BLU_FG << ITALIC << "Dog Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	this->_type = "Dog";
}

Dog::Dog(const Dog &val) : Animal(val) {
	std::cout << MAG_FG << ITALIC << "Dog Copy constructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
	*this = val;
}

Dog::~Dog() {
	std::cout << YEL_FG << ITALIC << "Dog Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

Dog &Dog::operator=(const Dog &rhs) {
	std::cout << MAG_FG << ITALIC << "Dog Copy assignment " << RESET << ITALIC
			  << "operator called" << RESET << std::endl;
	this->_type = rhs.getType();
	return (*this);
}

/* PUBLIC METHOD */

void Dog::makeSound() const {
	std::cout << "waouf";
}
