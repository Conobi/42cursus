/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:09:41 by conobi            #+#    #+#             */
/*   Updated: 2022/12/26 18:14:59 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

/* ORTHODOX FORM COMPLIANCE */

Cat::Cat() {
	std::cout << BLU_FG << ITALIC
		<< "Cat Default constructor " << RESET
		<< ITALIC << "called" << RESET << std::endl;
	this->_type = "Cat";
	this->_brain = new Brain;
}

Cat::Cat(const Cat &val) : Animal(val) {
	std::cout << MAG_FG << ITALIC
		<< "Cat Copy constructor " << RESET
		<< ITALIC << "called" << RESET << std::endl;
	this->_brain = new Brain;
	*this = val;
}

Cat::~Cat() {
	this->debugAddresses();
	std::cout << YEL_FG << ITALIC
	<< "Cat Destructor " << RESET
	<< ITALIC << "called" << RESET << std::endl;
	delete this->_brain;
}

Cat &Cat::operator=(const Cat &rhs) {
	std::cout << MAG_FG << ITALIC
	<< "Cat Copy assignment " << RESET
	<< ITALIC << "operator called" << RESET << std::endl;
	this->_type = rhs.getType();
	*(this->_brain) = rhs.getBrain();
	return (*this);
}

/* REQUIRED METHOD FOR COPY */

Brain &Cat::getBrain() const {

	return (*this->_brain);
}

/* PUBLIC METHOD */

void Cat::makeSound() const {

	std::cout << "miaou";
}

void Cat::debugAddresses() const {
	const std::string *ideas;

	std::cout << "type: " << this->_type << " (" << &(this->_type) << ")" << std::endl
		<< "brain address: " << &(this->_brain) << std::endl
		<< "ideas addresses:" << std::endl;
	
	ideas = this->_brain->getIdeas();
	for (size_t i = 1; i < 101; i++) {

		std::cout << &ideas[i - 1] << " ";
		if (!(i % 5))
			std::cout << std::endl;
	}
	
}