/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:41:48 by conobi            #+#    #+#             */
/*   Updated: 2022/11/29 18:12:17 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type): _type(type) {

}

Weapon::~Weapon() {

}

const std::string &Weapon::getType(void) {
	std::string &ret = this->_type;

	return (ret);
}

void Weapon::setType(std::string type) {
	this->_type = type;
}
