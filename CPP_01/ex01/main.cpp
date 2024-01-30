/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 19:31:53 by conobi            #+#    #+#             */
/*   Updated: 2022/11/29 15:56:26 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main (void) {
	Zombie *horde;
	size_t n = 42;

	horde = zombieHorde(n, "Smith");

	for (size_t i = 0; i < n; i++)
		horde[i].announce();

	delete [] (horde);
	return (0);
}
