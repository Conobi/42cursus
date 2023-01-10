/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:13:44 by conobi            #+#    #+#             */
/*   Updated: 2023/01/10 14:37:54 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

/* ORTHODOX FORM COMPLIANCE */

Dog::Dog() {
	std::cout << BLU_FG << ITALIC << "Dog Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	this->_type = "Dog";
	this->_brain = new Brain;
}

Dog::Dog(const Dog &val) : Animal(val) {
	std::cout << MAG_FG << ITALIC << "Dog Copy constructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
	*this = val;
}

Dog::~Dog() {
	std::cout << YEL_FG << ITALIC << "Dog Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
	delete this->_brain;
}

Dog &Dog::operator=(const Dog &rhs) {
	std::cout << MAG_FG << ITALIC << "Dog Copy assignment " << RESET << ITALIC
			  << "operator called" << RESET << std::endl;
	this->_type = rhs.getType();
	*(this->_brain) = rhs.getBrain();
	return (*this);
}

/* REQUIRED METHOD FOR COPY */

Brain &Dog::getBrain() const {
	return (*this->_brain);
}

/* PUBLIC METHOD */

void Dog::makeSound() const {
	std::cout << "waouf";
}

void Dog::debugAddresses() const {
	const std::string *ideas;

	std::cout << "type: " << this->_type << " (" << &(this->_type) << ")"
			  << std::endl
			  << "brain address: " << &(this->_brain) << std::endl
			  << "ideas addresses:" << std::endl;

	ideas = this->_brain->getIdeas();
	for (size_t i = 1; i < 101; i++) {
		std::cout << &ideas[i - 1] << " ";
		if (!(i % 5))
			std::cout << std::endl;
	}
}
