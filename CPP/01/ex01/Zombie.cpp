/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:30:18 by conobi            #+#    #+#             */
/*   Updated: 2022/11/29 16:06:18 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie() {
	std::cout
		<< BLU_FG
		<< "A dummy zombie has been created."
		<< RESET << std::endl;
}

void Zombie::setName(std::string name) {
	this->_name = name;
	std::cout
		<< BLU_FG
		<< "The dummy zombie has been named "
		<< name
		<< RESET << std::endl;
}

Zombie::~Zombie() {
	std::cout
		<< BLU_FG
		<< _name << " has been destroyed."
		<< RESET << std::endl;
}

void Zombie::announce(void) {
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
