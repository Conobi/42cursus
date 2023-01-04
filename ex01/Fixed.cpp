/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:52:42 by conobi            #+#    #+#             */
/*   Updated: 2023/01/04 19:59:22 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void) : _value(0) {
	std::cout << BLU_FG << ITALIC << "Default constructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

Fixed::Fixed(const Fixed &val) {
	std::cout << MAG_FG << ITALIC << "Copy constructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
	*this = val;
}

Fixed::Fixed(const int val) {
	std::cout << MAG_FG << ITALIC << "Int constructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
	this->_value = std::roundf(val * std::pow(2, _fractional));
}

Fixed::Fixed(const float val) {
	std::cout << MAG_FG << ITALIC << "Float constructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
	this->_value = std::roundf(val * std::pow(2, _fractional));
}

Fixed::~Fixed() {
	std::cout << YEL_FG << ITALIC << "Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

Fixed &Fixed::operator=(const Fixed &rhs) {
	std::cout << MAG_FG << ITALIC << "Copy assignment " << RESET << ITALIC
			  << "operator called" << RESET << std::endl;
	this->_value = rhs.getRawBits();
	return (*this);
}

int Fixed::getRawBits(void) const {
	return (this->_value);
}

void Fixed::setRawBits(int const raw) {
	this->_value = raw;
}

int Fixed::toInt(void) const {
	return (this->_value >> this->_fractional);
}

float Fixed::toFloat(void) const {
	return ((float)this->_value / (float)(1 << this->_fractional));
}

std::ostream &operator<<(std::ostream &os, const Fixed &val) {
	os << val.toFloat();
	return (os);
}
