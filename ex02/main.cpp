/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:19:03 by conobi            #+#    #+#             */
/*   Updated: 2022/12/21 15:37:29 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

void testClapTrap(unsigned int loop) {
	ClapTrap *squad = new ClapTrap[3];

	squad[0] = ClapTrap("Edouard");
	squad[1] = ClapTrap("Dieumerci");
	squad[2] = ClapTrap("Bienvenue");

	for (size_t i = 0; i < loop; i++)
	{
		squad[0].attack(squad[2].getName());
		squad[2].takeDamage(squad[0].getDamage());
		squad[1].attack(squad[0].getName());
		squad[0].takeDamage(squad[1].getDamage());
		squad[2].attack(squad[1].getName());
		squad[1].takeDamage(squad[2].getDamage());

		squad[2].beRepaired(1);
		squad[1].beRepaired(1);
	}

	delete []squad;
}

void testScavTrap (unsigned int loop) {
	ScavTrap *squad = new ScavTrap[3];

	squad[0] = ScavTrap("Josiane");
	squad[1] = ScavTrap("Michelle");
	squad[2] = ScavTrap("Bertrude");

	for (size_t i = 0; i < loop; i++)
	{
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

	delete []squad;
}

void testFragTrap (unsigned int loop) {
	FragTrap *squad = new FragTrap[3];

	squad[0] = FragTrap("Günter");
	squad[1] = FragTrap("Sigmund");
	squad[2] = FragTrap("Wolfgang");

	for (size_t i = 0; i < loop; i++)
	{
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

	delete []squad;
}

int main(void) {
	unsigned int nb_loop = 12;

	testClapTrap(nb_loop);
	testScavTrap(nb_loop);
	testFragTrap(nb_loop);
	return (0);
}
