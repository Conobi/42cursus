/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:19:03 by conobi            #+#    #+#             */
/*   Updated: 2023/01/09 17:38:07 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

void testClapTrap(unsigned int loop) {
	ClapTrap *squad = new ClapTrap[3];

	squad[0] = ClapTrap("Edouard");
	squad[1] = ClapTrap("Dieumerci");
	squad[2] = ClapTrap("Bienvenue");

	// Check the values with Assignement constructor
	std::cout << squad[0] << std::endl;

	ClapTrap foo = ClapTrap();

	// Check the values with Default constructor
	std::cout << foo << std::endl;

	for (size_t i = 0; i < loop; i++) {
		squad[0].attack(squad[2].getName());
		squad[2].takeDamage(squad[0].getDamage());
		squad[1].attack(squad[0].getName());
		squad[0].takeDamage(squad[1].getDamage());
		squad[2].attack(squad[1].getName());
		squad[1].takeDamage(squad[2].getDamage());

		squad[2].beRepaired(1);
		squad[1].beRepaired(1);
	}

	delete[] squad;
}

void testScavTrap(unsigned int loop) {
	ScavTrap *squad = new ScavTrap[3];

	squad[0] = ScavTrap("Josiane");
	squad[1] = ScavTrap("Michelle");
	squad[2] = ScavTrap("Bertrude");

	// Check the values with Assignement constructor
	std::cout << squad[0] << std::endl;

	ClapTrap foo = ScavTrap();

	// Check the values with Default constructor
	std::cout << foo << std::endl;

	for (size_t i = 0; i < loop; i++) {
		squad[0].attack(squad[2].getName());
		squad[2].takeDamage(squad[0].getDamage());
		squad[1].attack(squad[0].getName());
		squad[0].takeDamage(squad[1].getDamage());
		squad[2].attack(squad[1].getName());
		squad[1].takeDamage(squad[2].getDamage());

		squad[2].beRepaired(1);
		squad[1].beRepaired(1);
	}

	squad[0].guardGate();
	squad[1].guardGate();
	squad[2].guardGate();

	delete[] squad;
}

void testFragTrap(unsigned int loop) {
	FragTrap *squad = new FragTrap[3];

	squad[0] = FragTrap("Günter");
	squad[1] = FragTrap("Sigmund");
	squad[2] = FragTrap("Wolfgang");

	// Check the values with Assignement constructor
	std::cout << squad[0] << std::endl;

	ClapTrap foo = FragTrap();

	// Check the values with Default constructor
	std::cout << foo << std::endl;

	for (size_t i = 0; i < loop; i++) {
		squad[0].attack(squad[2].getName());
		squad[2].takeDamage(squad[0].getDamage());
		squad[1].attack(squad[0].getName());
		squad[0].takeDamage(squad[1].getDamage());
		squad[2].attack(squad[1].getName());
		squad[1].takeDamage(squad[2].getDamage());

		squad[2].beRepaired(1);
		squad[1].beRepaired(1);
	}

	squad[0].highFivesGuys();
	squad[1].highFivesGuys();
	squad[2].highFivesGuys();

	delete[] squad;
}

int main(void) {
	unsigned int nb_loop = 12;

	std::cout << "------------------" << std::endl;
	testClapTrap(nb_loop);
	std::cout << "------------------" << std::endl;
	testScavTrap(nb_loop);
	std::cout << "------------------" << std::endl;
	testFragTrap(nb_loop);
	std::cout << "------------------" << std::endl;

	return (0);
}
