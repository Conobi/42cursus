/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:19:35 by conobi            #+#    #+#             */
/*   Updated: 2023/01/09 17:32:06 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

#include "ClapTrap.hpp"

/* ORTHODOX FORM COMPLIANCE */

ScavTrap::ScavTrap() : ClapTrap() {
	std::cout << BLU_FG << ITALIC << "ScavTrap Default constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	this->_name = "ScavTrap";
	this->_health = 100;
	this->_energy = 50;
	this->_damage = 20;
}

ScavTrap::ScavTrap(const ScavTrap &val) {
	std::cout << MAG_FG << ITALIC << "ScavTrap Copy constructor " << RESET
			  << ITALIC << "called" << RESET << std::endl;
	*this = val;
}

ScavTrap::~ScavTrap() {
	std::cout << YEL_FG << ITALIC << "ScavTrap Destructor " << RESET << ITALIC
			  << "called" << RESET << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &rhs) {
	std::cout << MAG_FG << ITALIC << "ScavTrap Copy assignment " << RESET
			  << ITALIC << "operator called" << RESET << std::endl;
	this->_name = rhs.getName();
	this->_health = rhs.getHealth();
	this->_damage = rhs.getDamage();
	this->_energy = rhs.getEnergy();
	return (*this);
}

/* ASSIGNEMENT CONSTRUCTOR */

ScavTrap::ScavTrap(const std::string name) : ClapTrap(name) {
	std::cout << BLU_FG << ITALIC << "ScavTrap Assignement constructor "
			  << RESET << ITALIC << "called for " << name << RESET << std::endl;
	this->_health = 100;
	this->_energy = 50;
	this->_damage = 20;
}

/* NEW METHOD */

void ScavTrap::attack(const std::string &target) {
	std::cout << "ScavTrap " << this->_name << " attacks " << target
			  << ", causing " << this->_damage << " points of damage!"
			  << std::endl;
}

void ScavTrap::guardGate() {
	std::cout << YEL_FG << this->getName()
			  << " was activated in the Gate Keeper mode." << RESET
			  << std::endl;
}
