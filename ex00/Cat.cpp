/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:09:41 by conobi            #+#    #+#             */
/*   Updated: 2023/01/06 02:05:49 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

/* ORTHODOX FORM COMPLIANCE */

Cat::Cat() {
	std::cout << BLU_FG << ITALIC << "Cat Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	this->_type = "Cat";
}

Cat::Cat(const Cat &val) : Animal(val) {
	std::cout << MAG_FG << ITALIC << "Cat Copy constructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
	*this = val;
}

Cat::~Cat() {
	std::cout << YEL_FG << ITALIC << "Cat Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

Cat &Cat::operator=(const Cat &rhs) {
	std::cout << MAG_FG << ITALIC << "Cat Copy assignment " << RESET << ITALIC
			  << "operator called" << RESET << std::endl;
	this->_type = rhs.getType();
	return (*this);
}

/* PUBLIC METHOD */

void Cat::makeSound() const {
	std::cout << "miaou";
}
