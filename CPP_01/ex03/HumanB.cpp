/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:42:32 by conobi            #+#    #+#             */
/*   Updated: 2022/11/29 18:22:57 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name): _name(name) {
	this->_club = NULL;
}

HumanB::~HumanB() {

}

void HumanB::attack(void) const {
	if (this->_club != NULL)
		std::cout
			<< this->_name << " attacks with their " << this->_club->getType()
			<< std::endl;
}

void HumanB::setWeapon(Weapon &club) {
	this->_club = &club;
}
