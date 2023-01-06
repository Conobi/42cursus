/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 02:28:13 by conobi            #+#    #+#             */
/*   Updated: 2023/01/06 02:08:13 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

/* ORTHODOX FORM COMPLIANCE */

Brain::Brain() {
	std::cout << BLU_FG << ITALIC << "Brain Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
}

Brain::Brain(const Brain &val) {
	std::cout << MAG_FG << ITALIC << "Brain Copy constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	*this = val;
}

Brain::~Brain() {
	std::cout << YEL_FG << ITALIC << "Brain Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

Brain &Brain::operator=(const Brain &rhs) {
	std::cout << MAG_FG << ITALIC << "Brain Copy assignment " << RESET << ITALIC
			  << "operator called" << RESET << std::endl;

	for (size_t i = 0; i < 100; i++) {
		this->_ideas[i] = rhs.getIdea(i);
	}
	return (*this);
}

const std::string *Brain::getIdeas() const {
	return (this->_ideas);
}

const std::string Brain::getIdea(size_t index) const {
	if (index < 100)
		return (this->_ideas[index]);
	return (NULL);
}

void Brain::setIdea(size_t index, std::string str) {
	if (index < 100)
		this->_ideas[index] = str;
}
