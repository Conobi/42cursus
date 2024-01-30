/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:10:06 by conobi            #+#    #+#             */
/*   Updated: 2023/01/10 14:45:45 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

/* ORTHODOX FORM COMPLIANCE */

AAnimal::AAnimal() {
	std::cout << BLU_FG << ITALIC << "AAnimal Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	this->_type = "Animal";
}

AAnimal::AAnimal(const AAnimal &val) {
	std::cout << MAG_FG << ITALIC << "AAnimal Copy constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	*this = val;
}

AAnimal::~AAnimal() {
	std::cout << YEL_FG << ITALIC << "AAnimal Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal &rhs) {
	std::cout << MAG_FG << ITALIC << "AAnimal Copy assignment " << RESET
			  << ITALIC << "operator called" << RESET << std::endl;
	this->_type = rhs.getType();
	return (*this);
}

/* REQUIRED METHOD FOR COPY */

std::string AAnimal::getType() const {
	return (this->_type);
}

/* PUBLIC METHOD */

void AAnimal::debugAddresses() const {
	std::cout << "type: " << this->_type << " (" << &(this->_type) << ")"
			  << std::endl;
}
