/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:19:03 by conobi            #+#    #+#             */
/*   Updated: 2022/12/21 15:25:42 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

void testClapTrap() {
	ClapTrap *squad = new ClapTrap[3];

	squad[0] = ClapTrap("Edouard");
	squad[1] = ClapTrap("Dieumerci");
	squad[2] = ClapTrap("Bienvenue");

	for (size_t i = 0; i < 12; i++)
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

int main(void) {

	testClapTrap();
	return (0);
}
