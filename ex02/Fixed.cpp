/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:52:42 by conobi            #+#    #+#             */
/*   Updated: 2023/01/04 20:01:19 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

/*
	CONSTRUCTORS AND DESTRUCTOR
*/

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
	this->_value = std::roundf(val * std::pow(2, this->_fractional));
}

Fixed::Fixed(const float val) {
	std::cout << MAG_FG << ITALIC << "Float constructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
	this->_value = std::roundf(val * std::pow(2, this->_fractional));
}

Fixed::~Fixed() {
	std::cout << YEL_FG << ITALIC << "Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

/*
	OPERATOR OVERLOADS THAT CHANGES THE VALUE
*/

Fixed &Fixed::operator=(const Fixed &rhs) {
	std::cout << MAG_FG << ITALIC << "Copy assignment " << RESET << ITALIC
			  << "operator called" << RESET << std::endl;
	this->_value = rhs.getRawBits();
	return (*this);
}

Fixed &Fixed::operator++() {
	this->_value++;
	return (*this);
}

Fixed Fixed::operator++(int) {
	Fixed tmp(*this);

	operator++();
	return (tmp);
}

Fixed &Fixed::operator--() {
	this->_value--;
	return (*this);
}

Fixed Fixed::operator--(int) {
	Fixed tmp(*this);

	operator--();
	return (tmp);
}

/*
	ARITHMETIC OVERLOADS
*/

Fixed Fixed::operator+(const Fixed &rhs) const {
	float val_a;
	float val_b;

	val_a = this->toFloat();
	val_b = rhs.toFloat();

	return (Fixed(val_a + val_b));
}

Fixed Fixed::operator-(const Fixed &rhs) const {
	float val_a;
	float val_b;

	val_a = this->toFloat();
	val_b = rhs.toFloat();

	return (Fixed(val_a - val_b));
}

Fixed Fixed::operator*(const Fixed &rhs) const {
	float val_a;
	float val_b;

	val_a = this->toFloat();
	val_b = rhs.toFloat();

	return (Fixed(val_a * val_b));
}

Fixed Fixed::operator/(const Fixed &rhs) const {
	float val_a;
	float val_b;

	val_a = this->toFloat();
	val_b = rhs.toFloat();

	return (Fixed(val_a / val_b));
}

/*
	COMPARISON OVERLOADS
*/

bool Fixed::operator>(const Fixed &rhs) const {
	float val_a;
	float val_b;

	val_a = this->toFloat();
	val_b = rhs.toFloat();

	return (val_a > val_b);
}

bool Fixed::operator<(const Fixed &rhs) const {
	float val_a;
	float val_b;

	val_a = this->toFloat();
	val_b = rhs.toFloat();

	return (val_a < val_b);
}

bool Fixed::operator>=(const Fixed &rhs) const {
	float val_a;
	float val_b;

	val_a = this->toFloat();
	val_b = rhs.toFloat();

	return (val_a >= val_b);
}

bool Fixed::operator<=(const Fixed &rhs) const {
	float val_a;
	float val_b;

	val_a = this->toFloat();
	val_b = rhs.toFloat();

	return (val_a <= val_b);
}

bool Fixed::operator==(const Fixed &rhs) const {
	float val_a;
	float val_b;

	val_a = this->toFloat();
	val_b = rhs.toFloat();

	return (val_a == val_b);
}

bool Fixed::operator!=(const Fixed &rhs) const {
	float val_a;
	float val_b;

	val_a = this->toFloat();
	val_b = rhs.toFloat();

	return (val_a != val_b);
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
	if (a < b) {
		return (a);
	}
	return (b);
}

const Fixed &Fixed::min(Fixed const &a, Fixed const &b) {
	if (a < b) {
		return (a);
	}
	return (b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
	if (a > b) {
		return (a);
	}
	return (b);
}

const Fixed &Fixed::max(Fixed const &a, Fixed const &b) {
	if (a > b) {
		return (a);
	}
	return (b);
}

/*
	PUBLIC MEMBER FUNCTIONS
*/

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

/*
	STREAM OVERLOAD
*/

std::ostream &operator<<(std::ostream &os, const Fixed &val) {
	os << val.toFloat();
	return (os);
}
