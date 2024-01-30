/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:02:16 by conobi            #+#    #+#             */
/*   Updated: 2023/01/06 02:09:05 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

/* ORTHODOX FORM COMPLIANCE */

WrongAnimal::WrongAnimal() {
	std::cout << BLU_FG << ITALIC << "WrongAnimal Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	this->_type = "WrongAnimal";
}

WrongAnimal::WrongAnimal(const WrongAnimal &val) {
	std::cout << MAG_FG << ITALIC << "WrongAnimal Copy constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	*this = val;
}

WrongAnimal::~WrongAnimal() {
	std::cout << YEL_FG << ITALIC << "WrongAnimal Destructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &rhs) {
	std::cout << MAG_FG << ITALIC << "WrongAnimal Copy assignment " << RESET
			  << ITALIC << "operator called" << RESET << std::endl;
	this->_type = rhs.getType();
	return (*this);
}

/* REQUIRED METHOD FOR COPY */

std::string WrongAnimal::getType() const {
	return (this->_type);
}

/* PUBLIC METHOD */

void WrongAnimal::makeSound() const {
	std::cout << "krr";
}
