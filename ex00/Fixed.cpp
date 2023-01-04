/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:52:42 by conobi            #+#    #+#             */
/*   Updated: 2023/01/04 19:44:14 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void) : _value(0) {
	std::cout << BLU_FG << ITALIC << "Default constructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

Fixed::Fixed(Fixed &cpy) {
	std::cout << MAG_FG << ITALIC << "Copy constructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
	this->_value = cpy.getRawBits();
}

Fixed::~Fixed() {
	std::cout << YEL_FG << ITALIC << "Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

Fixed &Fixed::operator=(Fixed &rhs) {
	std::cout << MAG_FG << ITALIC << "Copy assignment " << RESET << ITALIC
			  << "operator called" << RESET << std::endl;
	this->_value = rhs.getRawBits();
	return (*this);
}

int Fixed::getRawBits(void) const {
	std::cout << ITALIC << "getRawBits member funciton called" << RESET
			  << std::endl;
	return (this->_value);
}

void Fixed::setRawBits(int const raw) {
	std::cout << ITALIC << "setRawBits member funciton called" << RESET
			  << std::endl;
	this->_value = raw;
}
