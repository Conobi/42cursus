/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:19:35 by conobi            #+#    #+#             */
/*   Updated: 2022/12/21 15:39:24 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

/* ORTHODOX FORM COMPLIANCE */

ClapTrap::ClapTrap() {
	std::cout << BLU_FG << ITALIC
		<< "ClapTrap Default constructor " << RESET
		<< ITALIC << "called" << RESET << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &val) {
	std::cout << MAG_FG << ITALIC
		<< "ClapTrap Copy constructor " << RESET
		<< ITALIC << "called" << RESET << std::endl;
	*this = val;
}

ClapTrap::~ClapTrap() {
	std::cout << YEL_FG << ITALIC
	<< "ClapTrap Destructor " << RESET
	<< ITALIC << "called" << RESET << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &rhs) {
	std::cout << MAG_FG << ITALIC
	<< "ClapTrap Copy assignment " << RESET
	<< ITALIC << "operator called" << RESET << std::endl;
	this->_name = rhs.getName();
	this->_health = rhs.getHealth();
	this->_damage = rhs.getDamage();
	this->_energy = rhs.getEnergy();
	return (*this);
}

/* ASSIGNEMENT CONSTRUCTOR */

ClapTrap::ClapTrap(const std::string name):
	_name(name),
	_health(10),
	_energy(10),
	_damage(0)
{
	std::cout << BLU_FG << ITALIC
		<< "ClapTrap Assignement constructor " << RESET
		<< ITALIC << "called for " << name
		<< RESET << std::endl;
}

/* PUBLIC METHODS */

void ClapTrap::attack(const std::string &target) {
	std::cout << "ClapTrap " << this->_name
		<< " attacks " << target << ", causing "
		<< this->_damage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {

	if ((int)(this->_health - amount) < 0) {
		amount = this->_health;
	}
	if (this->_health > 0) {
		std::cout << "Outch! ClapTrap " << this->_name
			<< " takes "
			<< amount << " points of damage!" << std::endl;
		this->_health -= amount;
	}
	if (this->_health == 0) {
		std::cout << RED_FG << this->_name
			<< " is dead!" << RESET << std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount) {

	if (amount > this->_energy)
		amount = this->_energy;

	if (amount > 0)
		std::cout << "ClapTrap " << this->_name
			<< " heals and get back "
			<< amount << " health points! "
			<< "At the cost of "
			<< amount << " energy points. "
			<< "They now have " << this->_health
			<< " health points." << std::endl;
	else
		std::cout << "ClapTrap " << this->_name
			<< " lacks of energy, and can't heal anymore." << std::endl;
	this->_health += amount;
	this->_energy -= amount;
}

/* GETTERS */

std::string ClapTrap::getName() const {
	return (this->_name);
}

unsigned int ClapTrap::getHealth() const {
	return (this->_health);
}

unsigned int ClapTrap::getEnergy() const {
	return (this->_energy);
}

unsigned int ClapTrap::getDamage() const {
	return (this->_damage);
}
