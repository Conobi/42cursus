/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 02:28:13 by conobi            #+#    #+#             */
/*   Updated: 2022/12/26 15:16:33 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

/* ORTHODOX FORM COMPLIANCE */

Brain::Brain() {
	std::cout << BLU_FG << ITALIC
		<< "Brain Default constructor " << RESET
		<< ITALIC << "called" << RESET << std::endl;
}

Brain::Brain(const Brain &val) {
	std::cout << MAG_FG << ITALIC
		<< "Brain Copy constructor " << RESET
		<< ITALIC << "called" << RESET << std::endl;
	*this = val;
}

Brain::~Brain() {
	std::cout << YEL_FG << ITALIC
	<< "Brain Destructor " << RESET
	<< ITALIC << "called" << RESET << std::endl;
}

Brain &Brain::operator=(const Brain &rhs) {
	std::cout << MAG_FG << ITALIC
	<< "Brain Copy assignment " << RESET
	<< ITALIC << "operator called" << RESET << std::endl;
	
	for (size_t i = 0; i < 100; i++) {
		this->setIdea(i, rhs.getIdea(i));
	}	
	return (*this);
}

const std::string *Brain::getIdeas() const {

	return (this->_ideas);
}

const std::string Brain::getIdea(size_t index) const {

	return (this->_ideas[index]);
}

void Brain::setIdea(size_t index, std::string str) {
	if (index >= 0 && index <= 100)
		this->_ideas[index] = str;
}
