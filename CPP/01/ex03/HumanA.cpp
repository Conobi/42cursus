/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:42:54 by conobi            #+#    #+#             */
/*   Updated: 2022/11/29 18:12:42 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &club): _name(name), _club(club) {

}

HumanA::~HumanA() {
}

void HumanA::attack(void) const {
	std::cout
		<< this->_name << " attacks with their " << this->_club.getType()
		<< std::endl;
}
