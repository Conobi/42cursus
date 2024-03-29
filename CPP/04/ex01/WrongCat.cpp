/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:16:06 by conobi            #+#    #+#             */
/*   Updated: 2023/01/06 02:09:12 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

/* ORTHODOX FORM COMPLIANCE */

WrongCat::WrongCat() {
	std::cout << BLU_FG << ITALIC << "WrongCat Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	this->_type = "WrongCat";
}

WrongCat::WrongCat(const WrongCat &val) : WrongAnimal(val) {
	std::cout << MAG_FG << ITALIC << "WrongCat Copy constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	*this = val;
}

WrongCat::~WrongCat() {
	std::cout << YEL_FG << ITALIC << "WrongCat Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &rhs) {
	std::cout << MAG_FG << ITALIC << "WrongCat Copy assignment " << RESET
			  << ITALIC << "operator called" << RESET << std::endl;
	this->_type = rhs.getType();
	return (*this);
}

/* PUBLIC METHOD */

void WrongCat::makeSound() const {
	std::cout << "miaou";
}
