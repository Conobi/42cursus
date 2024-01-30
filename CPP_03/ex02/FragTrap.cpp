/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:19:35 by conobi            #+#    #+#             */
/*   Updated: 2023/01/09 17:35:39 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

#include "ClapTrap.hpp"

/* ORTHODOX FORM COMPLIANCE */

FragTrap::FragTrap() : ClapTrap() {
	std::cout << BLU_FG << ITALIC << "FragTrap Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	this->_name = "FragTrap";
	this->_health = 100;
	this->_energy = 100;
	this->_damage = 30;
}

FragTrap::FragTrap(const FragTrap &val) {
	std::cout << MAG_FG << ITALIC << "FragTrap Copy constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	*this = val;
}

FragTrap::~FragTrap() {
	std::cout << YEL_FG << ITALIC << "FragTrap Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &rhs) {
	std::cout << MAG_FG << ITALIC << "FragTrap Copy assignment " << RESET
			  << ITALIC << "operator called" << RESET << std::endl;
	this->_name = rhs.getName();
	this->_health = rhs.getHealth();
	this->_damage = rhs.getDamage();
	this->_energy = rhs.getEnergy();
	return (*this);
}

/* ASSIGNEMENT CONSTRUCTOR */

FragTrap::FragTrap(const std::string name) : ClapTrap(name) {
	std::cout << BLU_FG << ITALIC << "FragTrap Assignement constructor "
			  << RESET << ITALIC << "called for " << name << RESET << std::endl;
	this->_health = 100;
	this->_energy = 100;
	this->_damage = 30;
}

/* NEW METHOD */

void FragTrap::attack(const std::string &target) {
	std::cout << "FragTrap " << this->_name << " attacks " << target
			  << ", causing " << this->_damage << " points of damage!"
			  << std::endl;
}

void FragTrap::highFivesGuys() {
	std::cout << YEL_FG << this->getName() << " is asking for an high five!"
			  << RESET << std::endl;
}
